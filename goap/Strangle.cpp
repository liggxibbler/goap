#include "Strangle.h"
#include "RoomManager.h"

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
	ConditionParameter sub(*GetArg(SEMANTIC_ROLE_AGENT));
	ConditionParameter obj(*GetArg(SEMANTIC_ROLE_PATIENT0));
	ConditionParameter ins(*GetArg(SEMANTIC_ROLE_INSTRUMENT));

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
	ConditionParameter sub, obj, inst, room;
	
	// SUBJECT
	sub.semantic = SEMANTIC_ROLE_AGENT;
	sub.instance = NULL;
	sub.type = OBJ_TYPE_AGENT;
	m_args.push_back(sub);

	// OBJECT
	obj.semantic = SEMANTIC_ROLE_PATIENT0;
	obj.instance = NULL;
	obj.type = OBJ_TYPE_AGENT;
	m_args.push_back(obj);

	//INSTRUMENT
	inst.semantic = SEMANTIC_ROLE_INSTRUMENT;
	inst.instance = NULL;
	inst.type = OBJ_TYPE_SQUEEZER | OBJ_TYPE_OBJECT;
	inst.strict = true;
	m_args.push_back(inst);

	// LOCATIVE
	room.semantic = SEMANTIC_ROLE_LOCATIVE;
	room.instance = NULL;
	inst.type = OBJ_TYPE_ROOM | OBJ_TYPE_OBJECT;
	inst.strict = true;
	m_args.push_back(room);
}

void Strangle::InitEffects()
{
	Condition objIsDead(OP_LAYOUT_TYPE_OAVB, OPER_TYPE_EQUAL);
	ConditionParameter obj = *GetArg(SEMANTIC_ROLE_PATIENT0);
	
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
	cpIter = GetArg(SEMANTIC_ROLE_AGENT);
	ConditionParameter sub(*cpIter);
	cpIter = GetArg(SEMANTIC_ROLE_INSTRUMENT);
	ConditionParameter inst(*cpIter);
	
	subHasInst[0] = sub;
	subHasInst[1] = inst;
	
	m_preconds->AddCondition(subHasInst);

	Condition subNearObj(OP_LAYOUT_TYPE_OAOAB, OPER_TYPE_EQUAL);
	
	cpIter = GetArg(SEMANTIC_ROLE_PATIENT0);
	ConditionParameter obj(*cpIter);
	
	subNearObj[0] = sub;
	subNearObj[0].attrib = ATTRIB_TYPE_ROOM;
	
	subNearObj[1] = obj;
	subNearObj[1].attrib = ATTRIB_TYPE_ROOM;
	
	m_preconds->AddCondition(subNearObj);
}

std::string Strangle::Express(Agent* agent)
{
	auto sub = GetArg(SEMANTIC_ROLE_AGENT);
	auto obj = GetArg(SEMANTIC_ROLE_PATIENT0);
	auto ins = GetArg(SEMANTIC_ROLE_INSTRUMENT);

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

int Strangle::Cost(RoomManager* rm)
{
	// return a measure of
	// 1 - how UNLIKELY it is to find the victim alone in the room
	// 2 - how UNLIKELY it is for the victim to be found after being killed

	int cost = 0;

	auto _patient = GetArg(SEMANTIC_ROLE_PATIENT0);
	auto _locative = GetArg(SEMANTIC_ROLE_LOCATIVE);
	Object* roomOwner = _locative->instance->GetOwner();

	if (roomOwner != 0)
	{
		cost += 1000 * rm->GetProb((Agent*)roomOwner, (Room*)_locative->instance);
	}
	if (roomOwner == _patient->instance)
	{
		cost += 500;
	}
	return cost;

	//return rand() % 1000;
}