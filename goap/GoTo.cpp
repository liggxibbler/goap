#include "GoTo.h"
#include "Room.h"

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

ActionStatus GoTo::ExecuteWorkhorse(int turn)
{
	ConditionParameter sub(*GetArgBySemantic(OP_SEMANTIC_ROLE_AGENT));
	ConditionParameter obj(*GetArgBySemantic(OP_SEMANTIC_ROLE_PATIENT0));

	Room* oldRoom = sub.instance->GetRoom();
	//sub.instance->SetAttrib(ATTRIB_TYPE_ROOM, (*(obj.instance))[ATTRIB_TYPE_ROOM]);
	Room* nextRoom = obj.instance->GetRoom();
	//sub.instance->SetRoom(room);
	
	if(oldRoom != nextRoom)
	{
		oldRoom->MarkForDeletion((Agent*)sub.instance);
		
		nextRoom->AddAgent((Agent*)(sub.instance));
		Agent* agent = dynamic_cast<Agent*>(sub.instance);
		agent->See(nextRoom);

		DUMP(Express(0))
	}

	return ACT_STAT_SUCCESS;
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
	sub.semantic = OP_SEMANTIC_ROLE_AGENT;
	sub.instance = m_agent;
	sub.type = OBJ_TYPE_AGENT;
	m_args.push_back(sub);

	// OBJECT
	obj1.semantic = OP_SEMANTIC_ROLE_PATIENT0;
	obj1.instance = m_dest;
	obj1.type = OBJ_TYPE_OBJECT;
	m_args.push_back(obj1);

}

void GoTo::InitEffects()
{
	Condition swapSubObj1(OP_LAYOUT_TYPE_OAOAB, OPER_TYPE_EQUAL);
	
	ConditionParameter sub(*GetArgBySemantic(OP_SEMANTIC_ROLE_AGENT));
	ConditionParameter obj0(*GetArgBySemantic(OP_SEMANTIC_ROLE_PATIENT0));
	
	swapSubObj1[0] = sub;
	swapSubObj1[0].attrib = ATTRIB_TYPE_ROOM;
	
	swapSubObj1[1] = obj0;
	swapSubObj1[1].attrib = ATTRIB_TYPE_ROOM;
	
	m_effects.push_back(swapSubObj1);	
}

void GoTo::InitPreconditions()
{
	// subject owns instrument
	Condition condTrue(OP_LAYOUT_TYPE_TRUE, OPER_TYPE_TRUE);
	m_preconds->AddCondition(condTrue);
}

std::string GoTo::Express(Agent* agent)
{
	auto sub = GetArgBySemantic(OP_SEMANTIC_ROLE_AGENT);
	auto obj = GetArgBySemantic(OP_SEMANTIC_ROLE_PATIENT0);
	
	std::string _agent;
	std::string _patient;

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
		_patient = "me";
	}
	else
	{
		_patient = obj->instance->GetName();
	}
	
	std::stringstream str;
	str << _agent << " went to " << _patient;
	return str.str();
}

GoTo::operator std::string()
{
	return "GoTo";
}