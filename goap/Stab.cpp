#include "Stab.h"

using namespace GOAP;

Stab::Stab()
{
	InitArgs();
	InitPreconditions();
	InitEffects();
}

Stab::Stab(const Stab& other)
{
}

Stab::~Stab()
{
}

void Stab::Execute()
{
}

Stab::operator ActionType()
{
	return ACTION_STAB;
}

Stab* Stab::Clone()
{
	Stab* newStab = new Stab();
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
	obj.semantic = OP_SEMANTIC_TYPE_OBJECT;
	obj.instance = NULL;
	obj.type = OBJ_TYPE_AGENT;
	m_args.push_back(obj);

	//INSTRUMENT
	inst.semantic = OP_SEMANTIC_TYPE_INSTRUMENT;
	inst.instance = NULL;
	inst.type = OBJ_TYPE_BLADE;
	m_args.push_back(inst);
}

void Stab::InitEffects()
{
	Condition objIsDead(OP_LAYOUT_TYPE_OAVB, OPER_TYPE_HAS_ATTIRB);
	ConditionParameter obj;
	// OBJECT
	obj.semantic	= OP_SEMANTIC_TYPE_OBJECT;
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
	ConditionParameter sub, inst;
	
	// subject
	sub.semantic	= OP_SEMANTIC_TYPE_SUBJECT;
	sub.instance	= NULL;
	sub.type		= OBJ_TYPE_AGENT;
	
	// instrument
	inst.semantic	= OP_SEMANTIC_TYPE_INSTRUMENT;
	inst.instance	= NULL;
	inst.type		= OBJ_TYPE_BLADE;
		
	subHasInst[0] = sub;
	subHasInst[1] = inst;
	subHasInst.SetNegate(false);
	m_effects.push_back(subHasInst);
}