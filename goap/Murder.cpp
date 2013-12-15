#include "Murder.h"
#include "RoomManager.h"

using namespace GOAP;

ExecutionStatus Murder::ExecuteWorkhorse(int turn)
{
	ConditionParameter sub(*GetArg(SEMANTIC_ROLE_AGENT));
	ConditionParameter obj(*GetArg(SEMANTIC_ROLE_PATIENT0));
	ConditionParameter ins(*GetArg(SEMANTIC_ROLE_INSTRUMENT));

	DUMP("       ** " << Express(0, 0))

	obj.instance->SetAttribute(ATTRIBUTE_ALIVE, false);
	Agent* agent = dynamic_cast<Agent*>(sub.instance);
	agent->DoneMurder(true);
	return EXEC_STAT_MURDER;
}

void Murder::InitArgs()
{
	ConditionParameter sub, obj, room;

	// SUBJECT
	sub.semantic = SEMANTIC_ROLE_AGENT;
	sub.instance = NULL;
	sub.type = OBJ_TYPE_AGENT | OBJ_TYPE_OBJECT;
	sub.strict = true;
	m_args.push_back(sub);

	// OBJECT
	obj.semantic = SEMANTIC_ROLE_PATIENT0;
	obj.instance = NULL;
	obj.type = OBJ_TYPE_AGENT | OBJ_TYPE_OBJECT;
	obj.strict = true;
	m_args.push_back(obj);

	// LOCATIVE
	room.semantic = SEMANTIC_ROLE_LOCATIVE;
	room.instance = NULL;
	room.type = OBJ_TYPE_ROOM | OBJ_TYPE_OBJECT;
	room.strict = true;
	m_args.push_back(room);
}

void Murder::InitEffects()
{
	Condition objIsDead(OP_LAYOUT_TYPE_OAVB, OPERATOR_EQUAL);
	ConditionParameter obj = *GetArg(SEMANTIC_ROLE_PATIENT0);

	objIsDead[0] = obj;
	objIsDead[0].attrib	= ATTRIBUTE_ALIVE;
	objIsDead[0].value	= false;
	objIsDead.SetNegate(false);

	m_effects.push_back(objIsDead);
}

void Murder::InitPreconditions()
{
	auto _agent(GetArg(SEMANTIC_ROLE_AGENT));
	auto _patient(GetArg(SEMANTIC_ROLE_PATIENT0));
	auto _instrument(GetArg(SEMANTIC_ROLE_INSTRUMENT));
	auto _locative(GetArg(SEMANTIC_ROLE_LOCATIVE));

	// AGENT owns INSTRUMENT
	Condition agentHasInst(OP_LAYOUT_TYPE_OOB, OPERATOR_HAS);

	agentHasInst[0] = *_agent;
	agentHasInst[1] = *_instrument;

	m_preconds->AddCondition(agentHasInst);

	// AGENT AT LOCATIVE

	Condition agentAtLoc(OP_LAYOUT_TYPE_OAOAB, OPERATOR_EQUAL);

	agentAtLoc[0] = *_agent;
	agentAtLoc[0].attrib = ATTRIBUTE_ROOM;

	agentAtLoc[1] = *_locative;
	agentAtLoc[1].attrib = ATTRIBUTE_ROOM;

	m_preconds->AddCondition(agentAtLoc);

	// PATIENT AT LOCATIVE

	Condition patientAtLoc(OP_LAYOUT_TYPE_OAOAB, OPERATOR_EQUAL);

	patientAtLoc[0] = *_patient;
	patientAtLoc[0].attrib = ATTRIBUTE_ROOM;

	patientAtLoc[1] = *_locative;
	patientAtLoc[1].attrib = ATTRIBUTE_ROOM;

	m_preconds->AddCondition(patientAtLoc);

	// AGENT ALONE WITH PATIENT

	/*Condition agentAloneWithPatient(OP_LAYOUT_TYPE_OAVB, OPERATOR_EQUAL);

	agentAloneWithPatient[0] = *_locative;
	agentAloneWithPatient[0].attrib = ATTRIBUTE_NUM_AGENTS;
	agentAloneWithPatient[0].value = 2;

	m_preconds->AddCondition(agentAloneWithPatient);*/

}

int Murder::Cost(RoomManager* rm)
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
		// penalty for suspicious activity
		cost += 500 * rm->GetProb((Agent*)roomOwner, (Room*)_locative->instance);
	}
	if (roomOwner == _patient->instance)
	{
		// penalty for suspicious activity
		cost += 500;
	}

	// penalty for risk of not being found
	cost += 1000.0f * (1.0f - rm->GetProbWillBeFound((Agent*)_patient->instance, (Room*)_locative->instance));

	// penalty for risk of not finding victim alone
	cost += 1000.f * (1.0f - rm->GetProbAlone((Agent*)_patient->instance, (Room*)_locative->instance));

	return cost;

	//return rand() % 1000;
}
