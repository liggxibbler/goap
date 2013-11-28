#include "GoTo.h"

using namespace GOAP;

GoTo::GoTo()
{
}

GoTo::GoTo(const GoTo& other)
{
}

GoTo::~GoTo()
{
}

ActionStatus GoTo::ExecuteWorkhorse()
{
	ConditionParameter sub(*GetArgBySemantic(OP_SEMANTIC_ROLE_AGENT));
	ConditionParameter obj(*GetArgBySemantic(OP_SEMANTIC_ROLE_PATIENT0));

	sub.instance->SetAttrib(ATTRIB_TYPE_POSX, (*(obj.instance))[ATTRIB_TYPE_POSX]);
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
	sub.instance = NULL;
	sub.type = OBJ_TYPE_AGENT;
	m_args.push_back(sub);

	// OBJECT
	obj1.semantic = OP_SEMANTIC_ROLE_PATIENT0;
	obj1.instance = NULL;
	obj1.type = OBJ_TYPE_OBJECT;
	m_args.push_back(obj1);
}

void GoTo::InitEffects()
{
	Condition swapSubObj1(OP_LAYOUT_TYPE_OAOAB, OPER_TYPE_EQUAL);
	
	ConditionParameter sub(*GetArgBySemantic(OP_SEMANTIC_ROLE_AGENT));
	ConditionParameter obj0(*GetArgBySemantic(OP_SEMANTIC_ROLE_PATIENT0));
	
	swapSubObj1[0] = sub;
	swapSubObj1[0].attrib = ATTRIB_TYPE_POSX;
	
	swapSubObj1[1] = obj0;
	swapSubObj1[1].attrib = ATTRIB_TYPE_POSX;
	
	m_effects.push_back(swapSubObj1);	
}

void GoTo::InitPreconditions()
{
	// subject owns instrument
	Condition condTrue(OP_LAYOUT_TYPE_TRUE, OPER_TYPE_TRUE);
	m_preconds->AddCondition(condTrue);
}