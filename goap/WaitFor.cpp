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
	//	(Agent*)(*GetArg(SemanticRole::AGENT));
	//}

	auto _goal = GetArg(SemanticRole::GOAL);
	auto _locative = GetArg(SemanticRole::LOCATIVE);

	if(_goal->instance->GetRoom() == _locative->instance->GetRoom())
	{
		return ExecutionStatus::SUCCESS;
	}
	else
	{
		DUMP("       ** " << Express(0, 0))
		/*m_turns--;*/
		return ExecutionStatus::RUNNING;
	}
}

WaitFor::operator ActionType()
{
	return ActionType::WAITFOR;
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
	sub.semantic = SemanticRole::AGENT;
	sub.instance = m_agent;
	sub.type = ObjectType::AGENT | ObjectType::OBJECT;
	sub.strict = true;
	m_args.push_back(sub);

	// OBJECT
	obj1.semantic = SemanticRole::GOAL;
	obj1.instance = m_dest;
	obj1.type = ObjectType::AGENT | ObjectType::OBJECT;
	sub.strict = true;
	m_args.push_back(obj1);

	// LOCATIVE
	loc.semantic = SemanticRole::LOCATIVE;
	loc.instance = nullptr;
	loc.type = ObjectType::ROOM | ObjectType::OBJECT;
	loc.strict = true;
	m_args.push_back(loc);

	m_turns = WAIT_TURNS;
}

void WaitFor::InitEffects()
{
	Condition goalAtLocation(OperatorLayoutType::OAOAB, OperatorType::EQUAL);
	
	Argument goal(*GetArg(SemanticRole::GOAL));
	Argument locative(*GetArg(SemanticRole::LOCATIVE));
	
	goalAtLocation[0] = goal;
	goalAtLocation[0].attrib = AttributeType::ROOM;
	
	goalAtLocation[1] = locative;
	goalAtLocation[1].attrib = AttributeType::ROOM;
	
	m_effects.push_back(goalAtLocation);


	/*Condition agentAloneWithPatient(OperatorLayoutType::OAVB, OperatorType::EQUAL);
		
	agentAloneWithPatient[0] = locative;
	agentAloneWithPatient[0].attrib = AttributeType::NUM_AGENTS;
	agentAloneWithPatient[0].value = 2;

	m_effects.push_back(agentAloneWithPatient);*/

}

void WaitFor::InitPreconditions()
{
	Condition agentAtLocative(OperatorLayoutType::OAOAB, OperatorType::EQUAL);
	
	agentAtLocative[0] = *GetArg(SemanticRole::AGENT);
	agentAtLocative[0].attrib = AttributeType::ROOM;

	agentAtLocative[1] = *GetArg(SemanticRole::LOCATIVE);
	agentAtLocative[1].attrib = AttributeType::ROOM;

	m_preconds->AddCondition(agentAtLocative);
}

std::string WaitFor::Express(Agent* agent, Room* room)
{
	auto sub = GetArg(SemanticRole::AGENT);
	auto obj = GetArg(SemanticRole::GOAL);
	
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

	auto _agent = GetArg(SemanticRole::AGENT);
	auto _room = GetArg(SemanticRole::GOAL);

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

	auto _agent = act->GetArg(SemanticRole::AGENT);
	auto _goal = act->GetArg(SemanticRole::GOAL);

	if(_goal->instance->GetCompoundType() != (ObjectType::OBJECT | ObjectType::AGENT))
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