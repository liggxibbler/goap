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

ExecutionStatus WaitFor::ExecuteWorkhorse(int turn)
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
		return EXEC_STAT_SUCCESS;
	}
	else
	{
		DUMP("       ** " << Express(0, 0))
		/*m_turns--;*/
		return EXEC_STAT_RUNNING;
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
	Argument sub, obj1, loc;
	
	// SUBJECT
	sub.semantic = SEMANTIC_ROLE_AGENT;
	sub.instance = m_agent;
	sub.type = OBJ_TYPE_AGENT | OBJ_TYPE_OBJECT;
	sub.strict = true;
	m_args.push_back(sub);

	// OBJECT
	obj1.semantic = SEMANTIC_ROLE_GOAL;
	obj1.instance = m_dest;
	obj1.type = OBJ_TYPE_AGENT | OBJ_TYPE_OBJECT;
	sub.strict = true;
	m_args.push_back(obj1);

	// LOCATIVE
	loc.semantic = SEMANTIC_ROLE_LOCATIVE;
	loc.instance = nullptr;
	loc.type = OBJ_TYPE_ROOM | OBJ_TYPE_OBJECT;
	loc.strict = true;
	m_args.push_back(loc);

	m_turns = WAIT_TURNS;
}

void WaitFor::InitEffects()
{
	Condition goalAtLocation(OP_LAYOUT_TYPE_OAOAB, OPERATOR_EQUAL);
	
	Argument goal(*GetArg(SEMANTIC_ROLE_GOAL));
	Argument locative(*GetArg(SEMANTIC_ROLE_LOCATIVE));
	
	goalAtLocation[0] = goal;
	goalAtLocation[0].attrib = ATTRIBUTE_ROOM;
	
	goalAtLocation[1] = locative;
	goalAtLocation[1].attrib = ATTRIBUTE_ROOM;
	
	m_effects.push_back(goalAtLocation);


	/*Condition agentAloneWithPatient(OP_LAYOUT_TYPE_OAVB, OPERATOR_EQUAL);
		
	agentAloneWithPatient[0] = locative;
	agentAloneWithPatient[0].attrib = ATTRIBUTE_NUM_AGENTS;
	agentAloneWithPatient[0].value = 2;

	m_effects.push_back(agentAloneWithPatient);*/

}

void WaitFor::InitPreconditions()
{
	Condition agentAtLocative(OP_LAYOUT_TYPE_OAOAB, OPERATOR_EQUAL);
	
	agentAtLocative[0] = *GetArg(SEMANTIC_ROLE_AGENT);
	agentAtLocative[0].attrib = ATTRIBUTE_ROOM;

	agentAtLocative[1] = *GetArg(SEMANTIC_ROLE_LOCATIVE);
	agentAtLocative[1].attrib = ATTRIBUTE_ROOM;

	m_preconds->AddCondition(agentAtLocative);
}

std::string WaitFor::Express(Agent* agent, Room* room)
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

	int cost = 5;

	auto _agent = GetArg(SEMANTIC_ROLE_AGENT);
	auto _room = GetArg(SEMANTIC_ROLE_GOAL);

	if(_room->instance == 0)
	{
		// THROW EXCEPTION
	}
	else if (_room->instance->GetRoom()->GetOwner() != 0 && _room->instance->GetRoom()->GetOwner() != _agent->instance)
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
	ArgIter cpIter;

	cpIter = act->m_args.begin();
	instanceIter = args.begin();

	for(unsigned int i=0; i<m_args.size(); ++i)
	{
		cpIter->instance = *(instanceIter++);
		++cpIter;
	}

	auto _agent = act->GetArg(SEMANTIC_ROLE_AGENT);
	auto _goal = act->GetArg(SEMANTIC_ROLE_GOAL);

	if(_goal->instance->GetCompoundType() != (OBJ_TYPE_OBJECT | OBJ_TYPE_AGENT))
	{
		return 0;
	}

	if(_agent->instance == _goal->instance)
	{
		return 0;
	}
	else
	{
		return act;
	}
}