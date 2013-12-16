#include "GoTo.h"
#include "Room.h"
#include "RoomManager.h"

using namespace GOAP;

GoTo::GoTo() : m_agent(0), m_dest(0)
{
}

GoTo::GoTo(const GoTo& other)
{
}

GoTo::GoTo(Room* room, Agent* agent) : m_agent(agent), m_dest(room)
{
}

GoTo::~GoTo()
{
}

ExecutionStatus GoTo::ExecuteWorkhorse(int turn)
{
	ConditionParameter sub(*GetArg(SEMANTIC_ROLE_AGENT));
	ConditionParameter obj(*GetArg(SEMANTIC_ROLE_GOAL));

	Room* oldRoom = sub.instance->GetRoom();
	//sub.instance->SetAttribute(ATTRIBUTE_ROOM, (*(obj.instance))[ATTRIBUTE_ROOM]);
	Room* nextRoom = obj.instance->GetRoom();
	//sub.instance->SetRoom(room);

	if( nextRoom == 0 )
	{
		if(obj.instance->GetAttrib(ATTRIBUTE_BEARER) == sub.instance->GetID())
		{
			return EXEC_STAT_SUCCESS;
		}
		else
		{
			// AND THROW AN EXCEPTION
			return EXEC_STAT_FAIL;
		}
	}

	if(oldRoom != nextRoom)
	{
		Agent* agent = (Agent*)(sub.instance);
		oldRoom->MarkForDeletion(agent);
		nextRoom->MarkForAddition(agent);
		agent->See(nextRoom);
	}

	DUMP("       ** " << Express(0, 0))

	return EXEC_STAT_SUCCESS;
}

GoTo::operator ActionType()
{
	return ACTION_GOTO;
}

GoTo* GoTo::Clone()
{
	GoTo* newGoTo = new GoTo();
	newGoTo->CloneData(this);
	return newGoTo;
}

void GoTo::InitArgs()
{
	ConditionParameter sub, obj1;

	// SUBJECT
	sub.semantic = SEMANTIC_ROLE_AGENT;
	sub.instance = m_agent;
	sub.type = OBJ_TYPE_AGENT | OBJ_TYPE_OBJECT;
	sub.strict = true;
	m_args.push_back(sub);

	// OBJECT
	obj1.semantic = SEMANTIC_ROLE_GOAL;
	obj1.instance = m_dest;
	obj1.type = OBJ_TYPE_OBJECT;
	m_args.push_back(obj1);

}

void GoTo::InitEffects()
{
	Condition agentNearGoal(OP_LAYOUT_TYPE_OAOAB, OPERATOR_EQUAL);

	ConditionParameter agent(*GetArg(SEMANTIC_ROLE_AGENT));
	ConditionParameter goal(*GetArg(SEMANTIC_ROLE_GOAL));

	agentNearGoal[0] = agent;
	agentNearGoal[0].attrib = ATTRIBUTE_ROOM;

	agentNearGoal[1] = goal;
	agentNearGoal[1].attrib = ATTRIBUTE_ROOM;

	m_effects.push_back(agentNearGoal);
}

void GoTo::InitPreconditions()
{
}

std::string GoTo::Express(Agent* agent, Room* room)
{
	auto sub = GetArg(SEMANTIC_ROLE_AGENT);
	auto obj = GetArg(SEMANTIC_ROLE_GOAL);

	std::string _agent;
	std::string _goal;
	std::string _verb;

	if(sub->instance == agent)
	{
		_agent = "I";
	}
	else
	{
		_agent = sub->instance->GetName();
	}

	if(obj->instance == room)
	{
		_verb = "came";
	}
	else
	{
		_verb = "went";
	}

	if(agent == 0)
	{
		_goal = obj->instance->GetRoom()->GetName();
	}
	else if(obj->instance->GetOwner() == agent)
	{
		_goal = "my bedroom";
	}
	else if(obj->instance->GetOwner() == sub->instance)
	{
		Agent* a = (Agent*)sub->instance;
		switch(a->GetGender())
		{
		case MALE:
			_goal = "his bedroom";
			break;
		case FEMALE:
			_goal = "her bedroom";
			break;
		default:
			break;
		}
	}
	else
	{
		_goal = obj->instance->GetRoom()->GetName();
	}

	std::stringstream str;
	str << _agent << " " << _verb << " to " << _goal;
	return str.str();
}

GoTo::operator std::string()
{
	return "GoTo";
}

int GoTo::Cost(RoomManager* rm)
{
	// return a measure of
	// 1 - how UNLIKELY it is for you to be here
	// 2 - if this is someone else's room (LIKELIHOOD of being caught)

	int cost = 5;

	auto _agent = GetArg(SEMANTIC_ROLE_AGENT);
	auto _room = GetArg(SEMANTIC_ROLE_GOAL);
	
	if(_room->instance == 0)
	{
		cost += 5;
	}
	else if (_room->instance->GetRoom() != 0)
	{
		if (_room->instance->GetRoom()->GetOwner() != 0 && _room->instance->GetRoom()->GetOwner() != _agent->instance)
		{
			cost += 100;
		}
	}

	return cost;
}

Action* GoTo::GetInstanceFromTuple(std::vector<Object*>& args)
{
	GoTo* act = Clone();
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

void GoTo::Dispatch(int turn)
{
	Action::Dispatch(turn);

	auto cp = GetArg(SEMANTIC_ROLE_GOAL);
	Room* room = cp->instance->GetRoom();
	for(auto agent(room->GetFirstAgent());agent != room->GetLastAgent();++agent)
	{
		(*agent)->Log(turn, this);
	}
}
