#include "WaitFor.h"
#include "Room.h"
#include "RoomManager.h"

using namespace GOAP;

WaitFor::WaitFor() : m_agent(0), m_dest(0)
{
}

WaitFor::WaitFor(const WaitFor& other)
{
}

WaitFor::WaitFor(Room* room, Agent* agent) : m_agent(agent), m_dest(room)
{
}

WaitFor::~WaitFor()
{
}

ActionStatus WaitFor::ExecuteWorkhorse(int turn)
{
	//if(m_turns == 0)
	//{
	//	/*append this to plan:
	//	goTo random room;
	//	goTo back here;
	//	wait for victim;*/
	//	(Agent*)(*GetArg(SEMANTIC_ROLE_AGENT));
	//}

	auto _goal = GetArg(SEMANTIC_ROLE_GOAL);
	auto _locative = GetArg(SEMANTIC_ROLE_LOCATIVE);

	if(_goal->instance->GetRoom() == _locative->instance->GetRoom())
	{
		return ACT_STAT_SUCCESS;
	}
	else
	{
		DUMP("       ** " << Express(0))
		/*m_turns--;*/
		return ACT_STAT_RUNNING;
	}
}

WaitFor::operator ActionType()
{
	return ACTION_WAITFOR;
}

WaitFor* WaitFor::Clone()
{
	WaitFor* newWaitFor = new WaitFor();
	newWaitFor->CloneData(this);
	return newWaitFor;
}

void WaitFor::InitArgs()
{
	ConditionParameter sub, obj1, loc;
	
	// SUBJECT
	sub.semantic = SEMANTIC_ROLE_AGENT;
	sub.instance = m_agent;
	sub.type = OBJ_TYPE_AGENT;
	m_args.push_back(sub);

	// OBJECT
	obj1.semantic = SEMANTIC_ROLE_GOAL;
	obj1.instance = m_dest;
	obj1.type = OBJ_TYPE_AGENT;
	m_args.push_back(obj1);

	// LOCATIVE
	loc.semantic = SEMANTIC_ROLE_LOCATIVE;
	loc.instance = NULL;
	loc.type = OBJ_TYPE_ROOM;
	loc.strict = true;
	m_args.push_back(loc);

	m_turns = WAIT_TURNS;
}

void WaitFor::InitEffects()
{
	Condition swapSubObj1(OP_LAYOUT_TYPE_OAOAB, OPER_TYPE_EQUAL);
	
	ConditionParameter sub(*GetArg(SEMANTIC_ROLE_GOAL));
	ConditionParameter obj0(*GetArg(SEMANTIC_ROLE_LOCATIVE));
	
	swapSubObj1[0] = sub;
	swapSubObj1[0].attrib = ATTRIB_TYPE_ROOM;
	
	swapSubObj1[1] = obj0;
	swapSubObj1[1].attrib = ATTRIB_TYPE_ROOM;
	
	m_effects.push_back(swapSubObj1);	
}

void WaitFor::InitPreconditions()
{
	Condition position(OP_LAYOUT_TYPE_OAOAB, OPER_TYPE_EQUAL);
	
	position[0] = *GetArg(SEMANTIC_ROLE_AGENT);
	position[0].attrib = ATTRIB_TYPE_ROOM;

	position[1] = *GetArg(SEMANTIC_ROLE_LOCATIVE);
	position[1].attrib = ATTRIB_TYPE_ROOM;

	m_preconds->AddCondition(position);
}

std::string WaitFor::Express(Agent* agent)
{
	auto sub = GetArg(SEMANTIC_ROLE_AGENT);
	auto obj = GetArg(SEMANTIC_ROLE_GOAL);
	
	std::string _agent;
	std::string _goal;
	std::string _verb("waited for");

	if(sub->instance == agent)
	{
		_agent = "I";
	}
	else
	{
		_agent = sub->instance->GetName();
	}

	if(obj->instance == agent)
	{
		_goal = "me";
	}
	else
	{
		_goal = obj->instance->GetName();
	}
	
	std::stringstream str;
	str << _agent << " " << _verb << " " << _goal;
	return str.str();
}

WaitFor::operator std::string()
{
	return "WaitFor";
}

int WaitFor::Cost(RoomManager* rm)
{
	// return a measure of
	// 1 - how UNLIKELY it is for you to be here
	// 2 - if this is someone else's room (LIKELIHOOD of being caught)

	int cost = 0;

	auto _agent = GetArg(SEMANTIC_ROLE_AGENT);
	auto _room = GetArg(SEMANTIC_ROLE_GOAL);

	if (_room->instance->GetRoom()->GetOwner() != 0 && _room->instance->GetRoom()->GetOwner() != _agent->instance)
	{
		cost += 100;
	}

	return cost;
}

void WaitFor::Dispatch(int turn)
{
	return;
}

Action* WaitFor::GetInstanceFromTuple(std::vector<Object*>& args)
{
	WaitFor* act = Clone();
	//act->Initialize(); // make sure arguments are initialized

	std::vector<Object*>::iterator instanceIter;
	CondParamIter cpIter;

	cpIter = act->m_args.begin();
	instanceIter = args.begin();

	for(unsigned int i=0; i<m_args.size(); ++i)
	{
		cpIter->instance = *(instanceIter++);
		++cpIter;
	}

	auto _agent = act->GetArg(SEMANTIC_ROLE_AGENT);
	auto _goal = act->GetArg(SEMANTIC_ROLE_GOAL);

	if(_agent->instance == _goal->instance)
	{
		return 0;
	}
	else
	{
		return act;
	}
}