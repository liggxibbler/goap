#include "Agent.h"
#include "Planner.h"
#include "Action.h"
#include "Room.h"
#include "RoomManager.h"
//#include "Wander.h"
#include "ActionRecord.h"

using namespace GOAP;

Agent::Agent() : m_goal(0), m_nextExecution(0), m_bDoneMurder(false),
				 m_isAlive(true), m_isMurderer(false), m_isVictim(false)
{
	m_attribs[ATTRIBUTE_HEIGHT] = &m_height;
	m_attribs[ATTRIBUTE_WEIGHT] = &m_weight;
	m_attribs[ATTRIBUTE_ALIVE] = &m_isAlive;
	m_planner = new Planner();
	m_plan = new Plan();
	m_plan->SetStatus(PLAN_STAT_UNKNOWN);
	See(this); // Know thyself
}

Agent::Agent(std::string name) : m_goal(0), m_nextExecution(0), m_bDoneMurder(false),
								 m_isAlive(true), m_isMurderer(false), m_isVictim(false)
{
	m_name = name;
	m_attribs[ATTRIBUTE_HEIGHT] = &m_height;
	m_attribs[ATTRIBUTE_WEIGHT] = &m_weight;
	m_attribs[ATTRIBUTE_ALIVE] = &m_isAlive;
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

	m_attribs[ATTRIBUTE_HEIGHT] = &m_height;
	m_attribs[ATTRIBUTE_WEIGHT] = &m_weight;
	m_attribs[ATTRIBUTE_ALIVE] = &m_isAlive;
}

void Agent::InitializeCharacter(RoomManager* rm, std::string name, Gender gender, std::string backStory, 
								int locationProbability[], bool canStab, bool canStrangle, 
								bool canShoot, bool canBludgeon, int height, int weight)
{
	m_name = name;
	m_height = height;
	m_weight = weight; 
	m_backStory = backStory;
	m_gender = gender;

	rm->AddAgentProbabilities(this, locationProbability);

	this->AddAction(ACTION_GOTO);

	for(int i = 0; i<NUMBER_OF_ROOMS; ++i)
	{
		if(i==0)
		{
			m_locationProbability[i] = locationProbability[i];
		}
		else
		{
			m_locationProbability[i] = locationProbability[i] + locationProbability[i-1];
		}
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

Agent::operator GOAP::ObjectType()
{
	return OBJ_TYPE_AGENT;
}

Goal* Agent::GetGoal()
{
	return m_goal;
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
			if(obj->GetCompoundType() & ot != 0)
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
	m_goal = goal;
}

Plan* Agent::GetPlan(ActionManager* am, Op::OperatorManager* om)
{
	//Plan* plan = new Plan();
	if( m_planner->Devise(this, am, om, m_plan) == PLAN_STAT_SUCCESS)
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
	
	if(m_isAlive)
	{
		if(m_nextExecution != 0)
		{
			ActionStatus as = m_nextExecution->Execute(om, turn);
			if (as == ACT_STAT_SUCCESS)
			{
				m_nextExecution = 0;
			}
			else if (as == ACT_STAT_SKIP)
			{
				m_nextExecution = 0;
				/*Update(om, rm, turn);*/
			}
		}
		else if(m_goal != 0)
		{
			GetPlan(ActionManager::Instance(), Op::OperatorManager::Instance());
			PlanStatus ps = m_plan->GetStatus();
			if(ps == PLAN_STAT_FAIL)
			{
				Room* room = rm->GetRandomRoom(this);
				GoTo* gt = new GoTo(room, this);
				gt->Initialize();
				m_nextExecution = gt;
			}
			else if (ps == PLAN_STAT_SUCCESS)
			{
				m_nextExecution = m_plan;
			}
			else
			{
				m_nextExecution = 0;
			}
		}
		else
		{
			int wander = rand() % 100;
			if(wander < 50)
			{
				DUMP("       **" << m_name << " be wanderin' " << turn)
					Room* room = rm->GetRandomRoom(this);
				GoTo* gt = new GoTo(room, this);
				gt->Initialize();
				m_nextExecution = gt;
			}
		}
	}
#ifdef _DEBUG
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
		std::cout << "'s dead!\n";
	}
#endif
	return m_bDoneMurder;
}

void Agent::Examine()
{
	Object::Examine();
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
	ActionRecord ar;
	for(unsigned int i=0; i<m_actionLog.size(); ++i)
	{
		ar = m_actionLog[i];
		std::cout << "At " << ar.turn << ", (" << ar.room->GetName() << ") " << m_actionLog[i].action->Express(this, ar.room) << std::endl;
	}
}

RoomName Agent::GetNextRoom()
{
	static RoomName rooms[] = {ROOM_KITCHEN, ROOM_LIVING_ROOM, ROOM_DINING_ROOM, ROOM_BATHROOM, ROOM_BEDROOM};
	
	int random = rand() % 100;
	
	int i;
	for (i=0; i<NUMBER_OF_ROOMS;++i)
	{
		if (random < m_locationProbability[i])
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