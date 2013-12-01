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

ActionStatus GoTo::ExecuteWorkhorse()
{
	ConditionParameter sub(*GetArgBySemantic(OP_SEMANTIC_ROLE_AGENT));
	ConditionParameter obj(*GetArgBySemantic(OP_SEMANTIC_ROLE_PATIENT0));

	//sub.instance->SetAttrib(ATTRIB_TYPE_ROOM, (*(obj.instance))[ATTRIB_TYPE_ROOM]);
	Room* room = obj.instance->GetRoom();
	sub.instance->SetRoom(room);
	Agent* agent = dynamic_cast<Agent*>(sub.instance);
	agent->See(room);

	DUMP(sub.instance->GetName() << " GoTo " << obj.instance->GetName())

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