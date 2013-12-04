#include "Agent.h"
#include "Planner.h"
#include "Action.h"
#include "Room.h"
#include "World.h"
//#include "Wander.h"
#include "ActionRecord.h"

using namespace GOAP;

Agent::Agent() : m_goal(0), m_nextExecution(0), m_bDoneMurder(false), 
				 m_isAlive(true), m_isMurderer(false), m_isVictim(false)
{
	m_attribs[ATTRIB_TYPE_HEIGHT] = &m_height;
	m_attribs[ATTRIB_TYPE_WEIGHT] = &m_weight;
	m_attribs[ATTRIB_TYPE_ALIVE] = &m_isAlive;
	m_planner = new Planner();
	m_plan = new Plan();
	m_plan->SetStatus(PLAN_STAT_UNKNOWN);
	See(this); // Know thyself
}

Agent::Agent(std::string name) : m_goal(0), m_nextExecution(0), m_bDoneMurder(false), 
								 m_isAlive(true), m_isMurderer(false), m_isVictim(false)
{
	m_name = name;
	m_attribs[ATTRIB_TYPE_HEIGHT] = &m_height;
	m_attribs[ATTRIB_TYPE_WEIGHT] = &m_weight;
	m_attribs[ATTRIB_TYPE_ALIVE] = &m_isAlive;
	m_planner = new Planner();
	m_plan = new Plan();
	m_plan->SetStatus(PLAN_STAT_UNKNOWN);
	See(this); // Know thyself
}

Agent::Agent(const Agent& other)
{
}

void Agent::InitializeCharacter(std::string name, Gender gender, std::string backStory, 
								int locationProbability[], bool canStab, bool canStrangle, 
								bool canShoot, bool canBludgeon, int height, int weight)
{
	m_name = name;
	m_height = height;
	m_weight = weight; 
	m_backStory = backStory;
	m_gender = gender;

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

bool Agent::Update(World* world, int turn)
{
	m_bDoneMurder = false;
	if(m_nextExecution != 0)
	{
		ActionStatus as = m_nextExecution->Execute(turn);
		if (as == ACT_STAT_SUCCESS)
		{
			m_nextExecution = 0;
		}
	}
	else if(m_goal != 0)
	{
		GetPlan(ActionManager::Instance(), Op::OperatorManager::Instance());
		PlanStatus ps = m_plan->GetStatus();
		if(ps == PLAN_STAT_FAIL)
		{
			Room* room = world->GetRandomRoom();
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
	m_actionLog.push_back(ar);
}

void Agent::See(Room* room)
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
			std::cout << m_actionLog[i].action->Express(this);
		}
	}*/
	GiveStatement();
}

void Agent::GiveStatement()
{
	for(unsigned int i=0; i<m_actionLog.size(); ++i)
	{
		std::cout << "At " << m_actionLog[i].turn << " " << m_actionLog[i].action->Express(this) << std::endl;
	}
}

RoomName Agent::GetNextRoom()
{
	static RoomName rooms[] = {ROOM_KITCHEN, ROOM_LIVING_ROOM, ROOM_DINING_ROOM, ROOM_BATHROOM, ROOM_BEDROOM};
	
	int random = rand() % 100;
	
	for (int i=0; i<NUMBER_OF_ROOMS;++i)
	{
		if (random < m_locationProbability[i])
		{
			return rooms[i];
		}
	}
}