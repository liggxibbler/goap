#include "Take.h"

using namespace GOAP;

Take::Take()
{
}

Take::Take(const Take& other)
{
}

Take::~Take()
{
}

Take::operator ActionType()
{
	return ACTION_TAKE;
}

ActionStatus Take::ExecuteWorkhorse()
{
	ConditionParameter sub(*GetArgBySemantic(OP_SEMANTIC_ROLE_AGENT));
	ConditionParameter obj(*GetArgBySemantic(OP_SEMANTIC_ROLE_PATIENT0));
	
	DUMP(sub.instance->GetName() << " Take " << obj.instance->GetName() )
	return ACT_STAT_SUCCESS;
}

Take* Take::Clone()
{
	Take* newTake = new Take();
	newTake->CloneData(this);
	return newTake;
}


void Take::InitArgs()
{
	ConditionParameter sub, obj;
	
	sub.semantic = OP_SEMANTIC_ROLE_AGENT;
	sub.instance = NULL;
	sub.type = OBJ_TYPE_AGENT;
	m_args.push_back(sub);

	obj.semantic = OP_SEMANTIC_ROLE_PATIENT0;
	obj.instance = NULL;
	obj.type = OBJ_TYPE_OBJECT;
	m_args.push_back(obj);
}

void Take::InitPreconditions()
{
	Condition subNearObj(OP_LAYOUT_TYPE_OAOAB, OPER_TYPE_EQUAL);
	ConditionParameter sub = *GetArgBySemantic(OP_SEMANTIC_ROLE_AGENT),
		obj = *GetArgBySemantic(OP_SEMANTIC_ROLE_PATIENT0);
	
	subNearObj[0] = sub;
	subNearObj[0].attrib = ATTRIB_TYPE_ROOM;

	subNearObj[1] = obj;
	subNearObj[1].attrib = ATTRIB_TYPE_ROOM;

	m_preconds->AddCondition(subNearObj);
}

void Take::InitEffects()
{
	Condition subHasObj(OP_LAYOUT_TYPE_OOB, OPER_TYPE_OWNS);
	ConditionParameter sub = *GetArgBySemantic(OP_SEMANTIC_ROLE_AGENT),
		obj = *GetArgBySemantic(OP_SEMANTIC_ROLE_PATIENT0);
	
	subHasObj[0] = sub;
	subHasObj[1] = obj;

	m_effects.push_back(subHasObj);
}