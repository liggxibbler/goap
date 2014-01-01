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

Agent::Agent() : m_currentGoal(0), m_nextExecution(0), m_bDoneMurder(false), m_updated(false),
				 m_isAlive(true), m_isMurderer(false), m_isVictim(false), m_inventory(false)
{
	InitAttribMap();
	m_planner = new Planner();
	m_plan = new Plan();
	m_plan->SetStatus(PLAN_STAT_UNKNOWN);
	See(this); // Know thyself
}

Agent::Agent(std::string name) : m_currentGoal(0), m_nextExecution(0), m_bDoneMurder(false), m_updated(false),
								 m_isAlive(true), m_isMurderer(false), m_isVictim(false), m_inventory(false)
{
	m_name = name;
	InitAttribMap();
	m_planner = new Planner();
	m_plan = new Plan();
	m_plan->SetStatus(PLAN_STAT_UNKNOWN);
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
								int locationProbability[], bool canStab, bool canStrangle,
								bool canShoot, bool canBludgeon, int height, int weight)
{
	this->AddAction(ACTION_GOTO);

	m_name = name;
	m_height = height;
	m_weight = weight;
	m_backStory = backStory;
	m_gender = gender;

	for(int i = 0; i<NUMBER_OF_ROOMS; ++i)
	{
		m_locationProbability[i] = locationProbability[i];	
	}

	//give actions based on the "can" booleans:
	if (canStab)
	{
		this->AddAction(ACTION_STAB);
	}
	if (canBludgeon)
	{
		this->AddAction(ACTION_BLUDGEON);
	}
	if (canShoot)
	{
		this->AddAction(ACTION_SHOOT);
	}
	if (canStrangle)
	{
		this->AddAction(ACTION_STRANGLE);
	}
}

Agent::~Agent()
{
}

//Agent::operator GOAP::ObjectType()
//{
//	return OBJ_TYPE_AGENT;
//}

Goal* Agent::GetGoal()
{
	return m_currentGoal;
}

std::list<ActionType>::iterator Agent::FirstAction()
{
	return m_actions.begin();
}

std::list<ActionType>::iterator Agent::LastAction()
{
	return m_actions.end();
}

std::map<int, Object*>::iterator Agent::FirstObject()
{
	return m_objects.begin();
}

std::map<int, Object*>::iterator Agent::LastObject()
{
	return m_objects.end();
}

bool Agent::Unify(int ot, std::vector<Object*>& result, bool strict)
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
			if((obj->GetCompoundType() & ot) != 0)
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

Plan* Agent::GetPlan(ActionManager* am, Op::OperatorManager* om)
{
	//Plan* plan = new Plan();
	if( m_planner->Devise(this, am, om, m_currentGoal->GetPlan()) == PLAN_STAT_SUCCESS)
	{
		DUMP("FOUND PLAN")
	}
	return m_plan;
}

void Agent::See(Object* obj)
{
	m_objects[obj->GetID()] = obj;
}

int Agent::GetCompoundType()
{
	return OBJ_TYPE_OBJECT | OBJ_TYPE_AGENT;
}

bool Agent::Update(Op::OperatorManager* om, RoomManager* rm, int turn)
{
	//m_bDoneMurder = false;

	if( m_isAlive && ( m_updated == false ) )
	{
		if(m_nextExecution != 0)
		{
			ExecutionStatus as = m_nextExecution->Execute(om, turn);
			if (as == EXEC_STAT_SUCCESS)
			{
				m_nextExecution = 0;
			}
			else if (as == EXEC_STAT_SKIP)
			{
				m_nextExecution = 0;
				/*Update(om, rm, turn);*/
			}
			else if(as == EXEC_STAT_DONE)
			{
				//m_currentGoal = m_currentGoal->GetParent();
				m_goals.remove(m_currentGoal);
				if(m_goals.size() > 0)
				{
					m_currentGoal = *(m_goals.begin());
				}
				else
				{
					m_currentGoal = 0;
				}

				m_nextExecution = 0;
				this->Update(om, rm, turn); // need replanning! must waist know thyme
			}
			else if(as == EXEC_STAT_FAIL)
			{
				m_plan = GetPlan(ActionManager::Instance(), om);
			}
		}
		else if(m_currentGoal != 0)
		{
			GetPlan(ActionManager::Instance(), Op::OperatorManager::Instance());
			PlanStatus ps = m_currentGoal->GetPlan()->GetStatus();
			if(ps == PLAN_STAT_FAIL)
			{
				Room* room = rm->GetRandomRoom(this);
				GoTo* gt = new GoTo(room, this);
				gt->Initialize();
				m_nextExecution = gt;
			}
			else if (ps == PLAN_STAT_SUCCESS)
			{
				m_nextExecution = m_currentGoal->GetPlan();
				this->Update(om, rm, turn); // XIBB?
			}
			else
			{
				m_nextExecution = 0;
			}
		}
		else
		{
			int wander = rand() % 100;
			if(wander < 90)
			{
				DUMP("       **" << m_name << " be wanderin' " << turn)
				Room* room = rm->GetRandomRoom(this);
				GoTo* gt = new GoTo(room, this);
				gt->Initialize();
				m_nextExecution = gt;
			}
		}
		m_updated = true;
	}
#ifdef _GOAP_DEBUG
	else
	{
		std::cout << "\n" << m_name << " can't update, ";
		switch(m_gender)
		{
		case MALE:
			std::cout << "he";
			break;
		case FEMALE:
			std::cout << "she";
			break;
		}
		std::cout << "'s either dead or up to date!\n";
	}
#endif
	return m_bDoneMurder;
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
		for(auto object(room->GetFirstObject());object != room->GetLastObject();++object)
		{
			See(*object);
		}

		for(auto agent(room->GetFirstAgent());agent != room->GetLastAgent();++agent)
		{
			See(*agent);
		}
	}
	See((Object*)room);
}

bool Agent::GetMurder()
{
	return m_bDoneMurder;
}

void Agent::DoneMurder(bool flag)
{
	m_bDoneMurder = flag;
}

void Agent::Answer(Object* obj, QuestionType qt, int turn)
{
	/*for(unsigned int i=0; i<m_actionLog.size();++i)
	{
		if(m_actionLog[i].turn == turn)
		{
			std::cout << m_actionLog[i].action->Express(this, m_actionLog[i].room);
		}
	}*/
	GiveStatement();
}

void Agent::GiveStatement()
{
	// Need to take victim and FactManager as arguments
	// Need FactManager
	// 

	int answer = -1;
	
	while(answer != 0)
	{
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
				ActionType at = *ar.action;
				int numWitness = ar.action->GetNumWitness();
				int numSuspect = ActionManager::Instance()->GetSuspicion(at);
				//actionIsSuspect = (numSuspect > 0); // XIBB

				if ( actionIsSuspect && (numWitness > numSuspect) &&
					(ar.action->GetArg(SEMANTIC_ROLE_AGENT)->instance == this))
				{
					//agentIsSuspect = true;// XIBB
				}
			}

			if(true)//!actionIsSuspect && !agentIsSuspect)// XIBB
			{
				if(oldTurn != ar.turn)
				{
					std::cout << i+1 << ". At " << TURN2TIME(ar.turn);
				}
				else
				{
					std::cout << i+1 << ".\t";
				}
				std::cout  << ", " << m_actionLog[i].action->Express(this, ar.room);
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
			auto room = m_actionLog[j].roomSnap;
			std::cout << "\nIn " << room->GetName() <<" at " << TURN2TIME(m_actionLog[j].turn) << " there was:\n\n";
			for(auto prop(room->GetFirstObject()); prop != room->GetLastObject(); ++prop)
			{
				std::cout << "-> " << (*prop)->GetName() << "\n";
			}
			for(auto agent(room->GetFirstAgent()); agent != room->GetLastAgent(); ++agent)
			{
				if(*agent == this)
				{
					std::cout << "-> Myself\n";
				}
				else
				{
					std::cout << "-> " << (*agent)->GetName() << "\n";
				}
			}
			std::cout << "\nPress any key to continue the interview" << std::endl;
			_getch();
		}
	}

}

RoomName Agent::GetNextRoom()
{
	static RoomName rooms[] = {ROOM_KITCHEN, ROOM_LIVING_ROOM, ROOM_DINING_ROOM, ROOM_BATHROOM, ROOM_BEDROOM};

	int random = rand() % 100;

	int i;
	int roullette = 0;
	for (i=0; i<NUMBER_OF_ROOMS;++i)
	{
		roullette += m_locationProbability[i];
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
	m_attribs[ATTRIBUTE_HEIGHT] = &m_height;
	m_attribs[ATTRIBUTE_WEIGHT] = &m_weight;
	m_attribs[ATTRIBUTE_ALIVE] = &m_isAlive;
	m_attribs[ATTRIBUTE_INVENTORY] = &m_inventory;
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

int* Agent::GetProbabilities()
{
	return m_locationProbability;
}

void Agent::AddGoal(Goal* goal)
{
	m_goals.push_back(goal);
	SortGoals();
	m_currentGoal = *(m_goals.begin());
}

void Agent::SortGoals()
{
	m_goals.sort(m_compare);
}