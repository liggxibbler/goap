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
	Argument sub(*GetArg(SemanticRole::AGENT));
	Argument obj(*GetArg(SemanticRole::GOAL));

	Room* oldRoom = sub.instance->GetRoom();
	//sub.instance->SetAttribute(AttributeType::ROOM, (*(obj.instance))[AttributeType::ROOM]);
	Room* nextRoom = obj.instance->GetRoom();
	//sub.instance->SetRoom(room);

	if( nextRoom == 0 )
	{
		if(obj.instance->GetAttrib(AttributeType::BEARER) == sub.instance->GetID())
		{
			return ExecutionStatus::SUCCESS;
		}
		else
		{
			// AND THROW AN EXCEPTION
			return ExecutionStatus::FAIL;
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

	return ExecutionStatus::SUCCESS;
}

GoTo::operator ActionType()
{
	return ActionType::GOTO;
}

GoTo* GoTo::Clone()
{
	GoTo* newGoTo = new GoTo();
	newGoTo->CloneData(this);
	return newGoTo;
}

void GoTo::InitArgs()
{
	Argument agent, goal;

	// SUBJECT
	agent.semantic = SemanticRole::AGENT;
	agent.instance = m_agent;
	agent.type = ObjectType::AGENT | ObjectType::OBJECT;
	agent.strict = true;
	m_args.push_back(agent);

	// OBJECT
	goal.semantic = SemanticRole::GOAL;
	goal.instance = m_dest;
	goal.type = ObjectType::OBJECT;
	m_args.push_back(goal);

}

void GoTo::InitEffects()
{
	Condition agentNearGoal(OperatorLayoutType::OAOAB, OperatorType::EQUAL);

	Argument agent(*GetArg(SemanticRole::AGENT));
	Argument goal(*GetArg(SemanticRole::GOAL));

	agentNearGoal.GetParamByIndex(0) = agent;
	agentNearGoal.GetParamByIndex(0).attrib = AttributeType::ROOM;

	agentNearGoal.GetParamByIndex(1) = goal;
	agentNearGoal.GetParamByIndex(1).attrib = AttributeType::ROOM;

	m_effects.push_back(agentNearGoal);
}

void GoTo::InitPreconditions()
{
}

std::string GoTo::Express(Agent* agent, Room* room)
{
	auto sub = GetArg(SemanticRole::AGENT);
	auto obj = GetArg(SemanticRole::GOAL);

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
		case Gender::MALE:
			_goal = "his bedroom";
			break;
		case Gender::FEMALE:
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
	int cost = 30;

	auto _agent = GetArg(SemanticRole::AGENT);
	auto _room = GetArg(SemanticRole::GOAL);
	
	if (_room->instance->GetRoom() != 0)
	{
		if (_room->instance->GetRoom()->GetOwner() != 0 && _room->instance->GetRoom()->GetOwner() != _agent->instance)
		{
			cost += 10;
		}
	}

	return cost;
}

Action* GoTo::GetInstanceFromTuple(std::vector<Object*>& args)
{
	GoTo* act = Clone();
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
	// Make sure the GoTo action's GOAL is a room, not an object
	GetArg(SemanticRole::GOAL)->instance = GetArg(SemanticRole::GOAL)->instance->GetRoom();
	Action::Dispatch(turn);

	auto cp = GetArg(SemanticRole::GOAL);
	Room* room = cp->instance->GetRoom();
	for(auto agent(room->GetFirstAgent());agent != room->GetLastAgent();++agent)
	{
		if((*agent)->IsVictim() == false)
		{
			m_numWitness++;
		}
		(*agent)->Log(turn, this);
	}
}

bool GoTo::MightSatisfy(Condition& cond)
{
	return Action::MightSatisfy(cond);
}