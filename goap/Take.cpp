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

ActionStatus Take::ExecuteWorkhorse(int turn)
{
	ConditionParameter sub(*GetArg(SEMANTIC_ROLE_AGENT));
	ConditionParameter obj(*GetArg(SEMANTIC_ROLE_PATIENT0));
	
	DUMP(Express(0))
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
	
	sub.semantic = SEMANTIC_ROLE_AGENT;
	sub.instance = NULL;
	sub.type = OBJ_TYPE_AGENT;
	m_args.push_back(sub);

	obj.semantic = SEMANTIC_ROLE_PATIENT0;
	obj.instance = NULL;
	obj.type = OBJ_TYPE_OBJECT;
	m_args.push_back(obj);
}

void Take::InitPreconditions()
{
	Condition subNearObj(OP_LAYOUT_TYPE_OAOAB, OPER_TYPE_EQUAL);
	ConditionParameter sub = *GetArg(SEMANTIC_ROLE_AGENT),
		obj = *GetArg(SEMANTIC_ROLE_PATIENT0);
	
	subNearObj[0] = sub;
	subNearObj[0].attrib = ATTRIB_TYPE_ROOM;

	subNearObj[1] = obj;
	subNearObj[1].attrib = ATTRIB_TYPE_ROOM;

	m_preconds->AddCondition(subNearObj);
}

void Take::InitEffects()
{
	Condition subHasObj(OP_LAYOUT_TYPE_OOB, OPER_TYPE_OWNS);
	ConditionParameter sub = *GetArg(SEMANTIC_ROLE_AGENT),
		obj = *GetArg(SEMANTIC_ROLE_PATIENT0);
	
	subHasObj[0] = sub;
	subHasObj[1] = obj;

	m_effects.push_back(subHasObj);
}

std::string Take::Express(Agent* agent)
{
	auto sub = GetArg(SEMANTIC_ROLE_AGENT);
	auto obj = GetArg(SEMANTIC_ROLE_PATIENT0);
	
	std::string _agent;
	std::string _patient;
	
	/// XIBB /// weirdest error. agent cannot be cast down to Object*. Why?

	if(sub->instance == (Object*)agent)
	{
		_agent = "I";
	}
	else
	{
		_agent = sub->instance->GetName();
	}

	if(obj->instance == (Object*)agent)
	{
		_patient = "me";
	}
	else
	{
		_patient = obj->instance->GetName();
	}

	std::stringstream str;
	str << _agent << " took " << _patient;

	return str.str();
}

Take::operator std::string()
{
	return "Take";
}

int Take::Cost()
{
	// return a measure of
	// 1 - if that thing doesn't BELONG to you
	// 2 - bonus points if it BELONGS to someone else, and not a room

	int cost = 0;

	auto _agent = GetArg(SEMANTIC_ROLE_AGENT);
	auto _patient = GetArg(SEMANTIC_ROLE_PATIENT0);

	if(_patient->instance->GetOwner() != _agent->instance)
	{
		cost += 50;
	}
	
	if(_patient->instance->GetOwner() != 0)
	{
		cost += 50;
	}	

	return cost;
}