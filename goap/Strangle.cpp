#include "Strangle.h"

using namespace GOAP;

Strangle::Strangle()
{
}

Strangle::Strangle(const Strangle& other)
{
}

Strangle::~Strangle()
{
}

ActionStatus Strangle::ExecuteWorkhorse(int turn)
{
	ConditionParameter sub(*GetArgBySemantic(OP_SEMANTIC_ROLE_AGENT));
	ConditionParameter obj(*GetArgBySemantic(OP_SEMANTIC_ROLE_PATIENT0));
	ConditionParameter ins(*GetArgBySemantic(OP_SEMANTIC_ROLE_INSTRUMENT));

	DUMP(Express(0))
	

	obj.instance->SetAttrib(ATTRIB_TYPE_ALIVE, false);
	Agent* agent = dynamic_cast<Agent*>(sub.instance);
	agent->DoneMurder(true);
	return ACT_STAT_MURDER;
}

Strangle::operator ActionType()
{
	return ACTION_STRANGLE;
}

Strangle* Strangle::Clone()
{
	Strangle* newStrangle = new Strangle();
	newStrangle->CloneData(this);
	return newStrangle;
}

void Strangle::InitArgs()
{
	ConditionParameter sub, obj, inst;
	
	// SUBJECT
	sub.semantic = OP_SEMANTIC_ROLE_AGENT;
	sub.instance = NULL;
	sub.type = OBJ_TYPE_AGENT;
	m_args.push_back(sub);

	// OBJECT
	obj.semantic = OP_SEMANTIC_ROLE_PATIENT0;
	obj.instance = NULL;
	obj.type = OBJ_TYPE_AGENT;
	m_args.push_back(obj);

	//INSTRUMENT
	inst.semantic = OP_SEMANTIC_ROLE_INSTRUMENT;
	inst.instance = NULL;
	inst.type = OBJ_TYPE_SQUEEZER | OBJ_TYPE_OBJECT;
	inst.strict = true;

	m_args.push_back(inst);
}

void Strangle::InitEffects()
{
	Condition objIsDead(OP_LAYOUT_TYPE_OAVB, OPER_TYPE_EQUAL);
	ConditionParameter obj = *GetArgBySemantic(OP_SEMANTIC_ROLE_PATIENT0);
	
	objIsDead[0] = obj;
	objIsDead[0].attrib	= ATTRIB_TYPE_ALIVE;
	objIsDead[0].value	= false;
	objIsDead.SetNegate(false);

	m_effects.push_back(objIsDead);
}

void Strangle::InitPreconditions()
{
	// subject owns instrument
	Condition subHasInst(OP_LAYOUT_TYPE_OOB, OPER_TYPE_OWNS);
	
	CondParamIter cpIter;
	cpIter = GetArgBySemantic(OP_SEMANTIC_ROLE_AGENT);
	ConditionParameter sub(*cpIter);
	cpIter = GetArgBySemantic(OP_SEMANTIC_ROLE_INSTRUMENT);
	ConditionParameter inst(*cpIter);
	
	subHasInst[0] = sub;
	subHasInst[1] = inst;
	
	m_preconds->AddCondition(subHasInst);

	Condition subNearObj(OP_LAYOUT_TYPE_OAOAB, OPER_TYPE_EQUAL);
	
	cpIter = GetArgBySemantic(OP_SEMANTIC_ROLE_PATIENT0);
	ConditionParameter obj(*cpIter);
	
	subNearObj[0] = sub;
	subNearObj[0].attrib = ATTRIB_TYPE_ROOM;
	
	subNearObj[1] = obj;
	subNearObj[1].attrib = ATTRIB_TYPE_ROOM;
	
	m_preconds->AddCondition(subNearObj);
}

std::string Strangle::Express(Agent* agent)
{
	auto sub = GetArgBySemantic(OP_SEMANTIC_ROLE_AGENT);
	auto obj = GetArgBySemantic(OP_SEMANTIC_ROLE_PATIENT0);
	auto ins = GetArgBySemantic(OP_SEMANTIC_ROLE_INSTRUMENT);

	std::string _agent;
	std::string _patient;
	std::string _instrument(ins->instance->GetName());

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
	str << _agent << " strangled " << _patient << " with " << _instrument;
	return str.str();
}

Strangle::operator std::string()
{
	return "Strangle";
}