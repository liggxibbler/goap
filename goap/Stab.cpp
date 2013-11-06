#include "Stab.h"

using namespace GOAP;

Stab::Stab()
{
}

Stab::Stab(const Stab& other)
{
}

Stab::~Stab()
{
}

ActionStatus Stab::Execute()
{
	ConditionParameter sub(*GetArgBySemantic(OP_SEMANTIC_TYPE_SUBJECT));
	ConditionParameter obj(*GetArgBySemantic(OP_SEMANTIC_TYPE_OBJECT0));
	ConditionParameter ins(*GetArgBySemantic(OP_SEMANTIC_TYPE_INSTRUMENT));

	DUMP(sub.instance->GetName() << " Stab " << obj.instance->GetName() << " with " << ins.instance->GetName())
	return ACT_STAT_SUCCESS;
}

Stab::operator ActionType()
{
	return ACTION_STAB;
}

Stab* Stab::Clone()
{
	Stab* newStab = new Stab();
	newStab->CloneData(this);
	return newStab;
}

void Stab::InitArgs()
{
	ConditionParameter sub, obj, inst;
	
	// SUBJECT
	sub.semantic = OP_SEMANTIC_TYPE_SUBJECT;
	sub.instance = NULL;
	sub.type = OBJ_TYPE_AGENT;
	m_args.push_back(sub);

	// OBJECT
	obj.semantic = OP_SEMANTIC_TYPE_OBJECT0;
	obj.instance = NULL;
	obj.type = OBJ_TYPE_AGENT;
	m_args.push_back(obj);

	//INSTRUMENT
	inst.semantic = OP_SEMANTIC_TYPE_INSTRUMENT;
	inst.instance = NULL;
	inst.type = OBJ_TYPE_BLADE | OBJ_TYPE_OBJECT;
	m_args.push_back(inst);
}

void Stab::InitEffects()
{
	Condition objIsDead(OP_LAYOUT_TYPE_OAVB, OPER_TYPE_EQUAL);
	ConditionParameter obj;
	// OBJECT
	obj.semantic	= OP_SEMANTIC_TYPE_OBJECT0;
	obj.instance	= NULL;
	obj.type		= OBJ_TYPE_AGENT;
	obj.attrib		= ATTRIB_TYPE_ALIVE;
	obj.value		= false;
	
	objIsDead[0] = obj;
	objIsDead.SetNegate(false);

	m_effects.push_back(objIsDead);
}

void Stab::InitPreconditions()
{
	// subject owns instrument
	Condition subHasInst(OP_LAYOUT_TYPE_OOB, OPER_TYPE_OWNS);
	CondParamIter cpIter;
	cpIter = GetArgBySemantic(OP_SEMANTIC_TYPE_SUBJECT);
	ConditionParameter sub(*cpIter);
	cpIter = GetArgBySemantic(OP_SEMANTIC_TYPE_INSTRUMENT);
	ConditionParameter inst(*cpIter);
	
	subHasInst[0] = sub;
	subHasInst[1] = inst;
	
	m_preconds->AddCondition(subHasInst);
}