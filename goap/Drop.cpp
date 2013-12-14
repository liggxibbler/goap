#include "Drop.h"
#include "RoomManager.h"

using namespace GOAP;

Drop::Drop()
{
}

Drop::Drop(const Drop& other)
{
}

Drop::~Drop()
{
}

Drop::operator ActionType()
{
	return ACTION_DROP;
}

ExecutionStatus Drop::ExecuteWorkhorse(int turn)
{
	auto _agent(GetArg(SEMANTIC_ROLE_AGENT));
	auto _patient(GetArg(SEMANTIC_ROLE_PATIENT0));

	_patient->instance->SetBearer(0);
	_patient->instance->SetRoom(_agent->instance->GetRoom());

	DUMP("       ** " << Express(0, 0))
	return EXEC_STAT_SUCCESS;
}

Drop* Drop::Clone()
{
	Drop* newDrop = new Drop();
	newDrop->CloneData(this);
	return newDrop;
}


void Drop::InitArgs()
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

void Drop::InitPreconditions()
{
	Condition agentHasPatient(OP_LAYOUT_TYPE_OOB, OPERATOR_HAS);
	ConditionParameter agent = *GetArg(SEMANTIC_ROLE_AGENT),
		patient = *GetArg(SEMANTIC_ROLE_PATIENT0);

	agentHasPatient[0] = agent;
	agentHasPatient[1] = patient;

	m_preconds->AddCondition(agentHasPatient);
}

void Drop::InitEffects()
{
	Condition agentDoesNotHavePatient(OP_LAYOUT_TYPE_OOB, OPERATOR_HAS);
	agentDoesNotHavePatient.SetNegate(true);

	ConditionParameter agent = *GetArg(SEMANTIC_ROLE_AGENT),
		patient = *GetArg(SEMANTIC_ROLE_PATIENT0);

	agentDoesNotHavePatient[0] = agent;
	agentDoesNotHavePatient[1] = patient;

	m_effects.push_back(agentDoesNotHavePatient);

	Condition patientAtAgent_sRoom(OP_LAYOUT_TYPE_OAOAB, OPERATOR_EQUAL);

	patientAtAgent_sRoom[0] = patient;
	patientAtAgent_sRoom[0].attrib = ATTRIBUTE_ROOM;

	patientAtAgent_sRoom[1] = agent;
	patientAtAgent_sRoom[1].attrib = ATTRIBUTE_ROOM;

	m_effects.push_back(patientAtAgent_sRoom);

	Condition agentInventoryEmpty(OP_LAYOUT_TYPE_OAVB, OPERATOR_EQUAL);

	agentInventoryEmpty[0] = agent;
	agentInventoryEmpty[0].attrib = ATTRIBUTE_INVENTORY;
	agentInventoryEmpty[0].value = 0;

	m_effects.push_back(agentInventoryEmpty);
}

std::string Drop::Express(Agent* agent, Room* room)
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

Drop::operator std::string()
{
	return "Drop";
}

int Drop::Cost(RoomManager* rm)
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
