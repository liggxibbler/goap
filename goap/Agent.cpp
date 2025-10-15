#include "Agent.h"
#include "Planner.h"
#include "Action.h"
#include "Room.h"
#include "RoomManager.h"
//#include "Wander.h"
#include "ActionRecord.h"
#include <conio.h>
#include <algorithm>

using namespace GOAP;

Agent::Agent() : m_currentGoal(0), m_nextExecution(0), m_hasCommittedMurder(false), m_updated(false),
				 m_isAlive(true), m_isMurderer(false), m_isVictim(false), m_inventory(false)
{
	InitAttribMap();
	//s_planner = new Planner();
	See(this); // Know thyself
}

Agent::Agent(std::string name) : m_currentGoal(0), m_nextExecution(0), m_hasCommittedMurder(false), m_updated(false),
								 m_isAlive(true), m_isMurderer(false), m_isVictim(false), m_inventory(false)
{
	m_name = name;
	InitAttribMap();
	See(this); // Know thyself
}

Agent::Agent(const Agent& other) : Object(other)
{

	m_height = other.m_height;
	m_weight = other.m_weight;
	m_isAlive = other.m_isAlive;
	m_inventory = other.m_inventory;

	InitAttribMap();
}

void Agent::InitializeCharacter(std::string name, Gender gender, std::string backStory,
								float roomProbabilities[], int room_count, std::string actions[], int action_count)
{
	this->AddAction(ActionType::GOTO);

	m_name = name;
	m_height = 0;
	m_weight = 0;
	m_backStory = backStory;
	m_gender = gender;

	// TODO NUMBER_OF_ROOMS can be infered from game config file
	for(int i = 0; i<NUMBER_OF_ROOMS; ++i)
	{
		m_roomProbabilities[i] = roomProbabilities[i];
	}

	// TODO actions need to be generic data as well
	for (int i = 0; i < action_count; ++i)
	{
		if (actions[i].compare("stab") == 0)
		{
			this->AddAction(ActionType::STAB);
		}
		else if (actions[i].compare("bludgeon") == 0)
		{
			this->AddAction(ActionType::BLUDGEON);
		}
		else if (actions[i].compare("shoot") == 0)
		{
			this->AddAction(ActionType::SHOOT);
		}
		else if (actions[i].compare("strangle") == 0)
		{
			this->AddAction(ActionType::STRANGLE);
		}
	}
}

Agent::~Agent()
{
}

//Agent::operator GOAP::ObjectType()
//{
//	return ObjectType::AGENT;
//}

Goal* Agent::GetGoal()
{
	return m_currentGoal;
}

const std::list<ActionType>& Agent::GetActions() const
{
	return m_actions;
}


std::map<int, Object*>::iterator Agent::FirstObject()
{
	return m_objects.begin();
}

std::map<int, Object*>::iterator Agent::LastObject()
{
	return m_objects.end();
}

bool Agent::Unify(ObjectType ot, std::vector<Object*>& result, bool strict)
{
	std::map<int, Object*>::iterator objIter;
	//iterate through list of objects
	for(objIter = m_objects.begin(); objIter != m_objects.end(); ++objIter)
	{
		//return if object.type = ot
		static Object* obj;
		obj = (*objIter).second;
		if(strict)
		{
			if(obj->GetCompoundType() == ot)
			{
				result.push_back(obj);
			}
		}
		else
		{
			if((obj->GetCompoundType() & ot) != ObjectType::NONE)
			{
				result.push_back(obj);
			}
		}
	}

	if(result.empty())
	{
		return false;
	}

	return true;
}

void Agent::AddAction(ActionType at)
{
	m_actions.push_back(at);
}

void Agent::SetGoal(Goal* goal)
{
	m_currentGoal = goal;
}

void Agent::See(Object* obj)
{
	m_objects[obj->GetID()] = obj;
}

ObjectType Agent::GetCompoundType() const
{
	return ObjectType::OBJECT | ObjectType::AGENT;
}

void GOAP::Agent::ExecuteNext(Planner& planner, int turn)
{
	ExecutionStatus as = m_nextExecution->Execute(planner.GetOperatorManager(), turn);
	
	switch (as)
	{
	case ExecutionStatus::SUCCESS:
		{
			m_nextExecution = nullptr;
			break;
		}
	case ExecutionStatus::SKIP:
		{
			m_nextExecution = nullptr;
			/*Update(om, rm, turn);*/
			break;
		}
	case ExecutionStatus::DONE:
		{
			//m_currentGoal = m_currentGoal->GetParent();
			m_goals.remove(m_currentGoal);

			if (false)//m_nextExecution->FollowupGoal() != 0)
			{
				//this->AddGoal(m_nextExecution->FollowupGoal());
			}
			else
			{
				PickCurrentGoal();
			}

			m_nextExecution = nullptr;
			Update(planner, turn); // need replanning! must waist know thyme
			return;
		}
	case ExecutionStatus::FAIL: // XIBB - this is very bad replanning!!!
		{
			m_currentGoal->GetPlan()->SetStatus(PlanStatus::FAIL);
			m_nextExecution = nullptr;
			return;
		}
	}
}

void Agent::Update(Planner& planner, int turn)
{
	//m_bDoneMurder = false;

	if( m_isAlive && !m_updated)
	{
		if(m_currentGoal)
		{
			if( PeekGoal() && ( m_currentGoal->GetPlan()->GetExecutionStatus() == ExecutionStatus::PAUSED ) )
			{
				m_currentGoal->GetPlan()->Resume();
				m_nextExecution = m_currentGoal->GetPlan();
			}
			else if( !PeekGoal() )
			{
				m_currentGoal->GetPlan()->Pause();
				PickCurrentGoal();
				m_nextExecution = nullptr;
			}
		}

		if(m_nextExecution)
		{
			ExecuteNext(planner, turn);
		}
		else if(m_currentGoal)
		{
			if(m_currentGoal->GetPlan()->GetStatus() == PlanStatus::SUCCESS)
			{
				m_nextExecution = m_currentGoal->GetPlan();
			}
			else
			{
				planner.Devise(this, m_currentGoal->GetPlan());
				PlanStatus ps = m_currentGoal->GetPlan()->GetStatus();
				if(ps == PlanStatus::FAIL)
				{
					m_nextExecution = planner.GetWander(this);
				}
			}
			Update(planner, turn); // XIBB?
		}
		else
		{
			int wander = rand() % 100;
			if(wander < 90)
			{
				DUMP("       **" << m_name << " be wanderin' " << turn)
				m_nextExecution = planner.GetWander(this);
			}
		}
		m_updated = true;
	}
#ifdef _DEBUG
	else
	{
		std::cout << "\n" << m_name << " can't update, ";
		switch(m_gender)
		{
		case Gender::MALE:
			std::cout << "he";
			break;
		case Gender::FEMALE:
			std::cout << "she";
			break;
		}
		std::cout << "'s either dead (" << m_isAlive << ") or up to date (" << m_updated << ") \n";
	}
#endif
}

void Agent::Examine()
{
	Interview();
}

bool Agent::CanBeMurderWeapon()
{
	return false;
}

void Agent::Interview()
{
}

void Agent::Log(int turn, Action* action)
{
	ActionRecord ar;
	ar.action = action;
	ar.turn = turn;
	ar.roomSnap = (Room*)m_roomInstance->Clone();
	ar.room = m_roomInstance;
	m_actionLog.push_back(ar);
}

void Agent::See(Room* room, bool deep)
{
	if(deep)
	{
		for(Object* object : room->GetObjects())
		{
			See(object);
		}

		for(Agent* agent : room->GetAgents())
		{
			See(agent);
		}
	}
	See((Object*)room);
}

bool Agent::GetHasCommittedMurder()
{
	return m_hasCommittedMurder;
}

void Agent::SetHasCommittedMurder(bool flag)
{
	m_hasCommittedMurder = flag;
}

void Agent::Answer(const ActionManager& actionManager, Object* obj, QuestionType qt, int turn)
{
	/*for(unsigned int i=0; i<m_actionLog.size();++i)
	{
		if(m_actionLog[i].turn == turn)
		{
			std::cout << m_actionLog[i].action->Express(this, m_actionLog[i].room);
		}
	}*/
	GiveStatement(actionManager);
}

void Agent::GiveStatement(const ActionManager& actionManager) const
{
	// Need to take victim and FactManager as arguments
	// Need FactManager
	//
	int answer = -1;

	while(answer != 0)
	{
		system("cls");

		ActionRecord ar;
		std::cout << "========================\n\n";
		std::cout << "You are interviewing " << m_name << ":\n\n";

		int oldTurn = -1;
		for(unsigned int i=0; i<m_actionLog.size(); ++i)
		{
			ar = m_actionLog[i];

			bool agentIsSuspect = false;
			bool actionIsSuspect = false;

			if(m_isMurderer)
			{
				ActionType at = ar.action->GetActionType();
				int numWitness = ar.action->GetNumWitness();
				int numSuspect = actionManager.GetSuspicion(at);
				//actionIsSuspect = (numSuspect > 0); // XIBB

				if ( actionIsSuspect && (numWitness > numSuspect) &&
					(ar.action->GetArg(SemanticRole::AGENT).instance == this))
				{
					//agentIsSuspect = true;// XIBB
				}
			}

			if(true)//!actionIsSuspect && !agentIsSuspect)// XIBB
			{
				std::cout.fill(' ');
				std::cout.width(2);
				if(oldTurn != ar.turn)
				{
					std::cout << i+1 << ". At " << TURN2TIME(ar.turn);
				}
				else
				{
					std::cout << i+1 << ".\t";
				}
				std::cout  << "\t| " << m_actionLog[i].action->Express(this, ar.room) << "\n";
			}

			if(agentIsSuspect)
			{
				std::cout << " [SUSPECT]";
			}

			std::cout << "\n";
			oldTurn = ar.turn;
		}

		std::cout << "\nEnter statement number for details, 0 to go back\n";
		std::cout << ">>> ";
		std::cin >> answer;
		unsigned int j = answer - 1;
		if( j>=0 && j < m_actionLog.size() )
		{
			const Room* room = m_actionLog[j].roomSnap;
			std::cout << "\nIn " << room->GetName() <<" at " << TURN2TIME(m_actionLog[j].turn) << " there was:\n\n";
			
			for(const Object* prop : room->GetObjects())
			{
				std::cout << "-> " << prop->GetName() << "\n";
			}
			
			for (const Agent* agent : room->GetAgents())
			{
				if(agent == this)
				{
					std::cout << "-> Myself\n";
				}
				else
				{
					std::cout << "-> " << agent->GetName() << "\n";
				}
			}
			std::cout << "\nPress any key to continue the interview" << std::endl;
			_getch();
		}
	}

}

RoomName Agent::GetNextRoom()
{
	static RoomName rooms[] = {RoomName::KITCHEN, RoomName::LIVING_ROOM, RoomName::DINING_ROOM, RoomName::BATHROOM, RoomName::BEDROOM};

	int random = rand() % 100;

	int i;
	float roullette = 0;
	for (i=0; i<NUMBER_OF_ROOMS;++i)
	{
		roullette += m_roomProbabilities[i];
		if (random < roullette)
		{
			return rooms[i];
		}
	}
	return rooms[i-1];
}

Object* Agent::Clone()
{
	return new Agent(*this);
}

Gender Agent::GetGender()
{
	return m_gender;
}

void Agent::InitAttribMap()
{
	Object::InitAttribMap();
	m_attribs[AttributeType::HEIGHT] = &m_height;
	m_attribs[AttributeType::WEIGHT] = &m_weight;
	m_attribs[AttributeType::ALIVE] = &m_isAlive;
	m_attribs[AttributeType::INVENTORY] = &m_inventory;
}

void Agent::ResetUpdateFlag()
{
	m_updated = false;
}

void Agent::Lie(ActionRecord& ar, unsigned int& numStatement)
{
	std::cout << numStatement+1 << ". At " << TURN2TIME(ar.turn) << ", " << m_actionLog[numStatement].action->Express(this, ar.room) << "\n";
}

void Agent::SetAsMurderer()
{
	m_isMurderer = true;
}
void Agent::ResetMurdererFlag()
{
	m_isMurderer = false;
}
bool Agent::IsMurderer()
{
	return m_isMurderer;
}

void Agent::SetAsVictim()
{
	m_isVictim = true;
}
void Agent::ResetVictimFlag()
{
	m_isVictim= false;
}
bool Agent::IsVictim()
{
	return m_isVictim;
}

bool GOAP::Agent::IsAlive()
{
	return m_isAlive;
}

const float* Agent::GetProbabilities() const
{
	return m_roomProbabilities;
}

void Agent::AddGoal(Goal* goal)
{
	m_goals.push_back(goal);
	SortGoals();
	//m_currentGoal = *(m_goals.begin());
}

void Agent::SortGoals()
{
	m_goals.sort(m_compare);
}

bool Agent::PeekGoal()
{
	if(m_currentGoal == 0)
	{
		return false;
	}

	if( m_goals.size() > 0 )
	{
		return ( m_currentGoal == m_goals.front() );
	}
	else
	{
		return false;
	}
}

void Agent::PickCurrentGoal()
{
	if( m_goals.size() > 0 )
	{
		m_currentGoal = m_goals.front();
	}
	else
	{
		m_currentGoal = 0;
	}
}

std::vector<ActionRecord>::iterator Agent::GetFirstActionRecord()
{
	return m_actionLog.begin();
}

std::vector<ActionRecord>::iterator Agent::GetLastActionRecord()
{
	return m_actionLog.end();
}
