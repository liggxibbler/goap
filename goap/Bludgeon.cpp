#include "Bludgeon.h"
#include "RoomManager.h"

using namespace GOAP;

Bludgeon::Bludgeon()
{
}

Bludgeon::Bludgeon(const Bludgeon& other)
{
}

Bludgeon::~Bludgeon()
{
}

ActionStatus Bludgeon::ExecuteWorkhorse(int turn)
{
	ConditionParameter sub(*GetArg(SEMANTIC_ROLE_AGENT));
	ConditionParameter obj(*GetArg(SEMANTIC_ROLE_PATIENT0));
	ConditionParameter ins(*GetArg(SEMANTIC_ROLE_INSTRUMENT));

	DUMP("       ** " << Express(0, 0))	

	obj.instance->SetAttrib(ATTRIB_TYPE_ALIVE, false);
	Agent* agent = dynamic_cast<Agent*>(sub.instance);
	agent->DoneMurder(true);
	return ACT_STAT_MURDER;
}

Bludgeon::operator ActionType()
{
	return ACTION_BLUDGEON;
}

Bludgeon* Bludgeon::Clone()
{
	Bludgeon* newBludgeon = new Bludgeon();
	newBludgeon->CloneData(this);
	return newBludgeon;
}

void Bludgeon::InitArgs()
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
	inst.type = OBJ_TYPE_BLUNT | OBJ_TYPE_OBJECT;
	inst.strict = true;
	m_args.push_back(inst);

	// LOCATIVE
	room.semantic = SEMANTIC_ROLE_LOCATIVE;
	room.instance = NULL;
	inst.type = OBJ_TYPE_ROOM | OBJ_TYPE_OBJECT;
	inst.strict = true;
	m_args.push_back(room);

}

void Bludgeon::InitEffects()
{
	Condition objIsDead(OP_LAYOUT_TYPE_OAVB, OPER_TYPE_EQUAL);
	ConditionParameter obj = *GetArg(SEMANTIC_ROLE_PATIENT0);
	
	objIsDead[0] = obj;
	objIsDead[0].attrib	= ATTRIB_TYPE_ALIVE;
	objIsDead[0].value	= false;
	objIsDead.SetNegate(false);

	m_effects.push_back(objIsDead);
}

void Bludgeon::InitPreconditions()
{
	auto _agent(GetArg(SEMANTIC_ROLE_AGENT));
	auto _patient(GetArg(SEMANTIC_ROLE_PATIENT0));
	auto _instrument(GetArg(SEMANTIC_ROLE_INSTRUMENT));
	auto _locative(GetArg(SEMANTIC_ROLE_LOCATIVE));

	// AGENT owns INSTRUMENT
	Condition agentHasInst(OP_LAYOUT_TYPE_OOB, OPER_TYPE_OWNS);
	
	agentHasInst[0] = *_agent;
	agentHasInst[1] = *_instrument;
	
	m_preconds->AddCondition(agentHasInst);

	// AGENT AT LOCATIVE

	Condition agentAtLoc(OP_LAYOUT_TYPE_OAOAB, OPER_TYPE_EQUAL);
	
	agentAtLoc[0] = *_agent;
	agentAtLoc[0].attrib = ATTRIB_TYPE_ROOM;
	
	agentAtLoc[1] = *_locative;
	agentAtLoc[1].attrib = ATTRIB_TYPE_ROOM;
	
	m_preconds->AddCondition(agentAtLoc);

	// PATIENT AT LOCATIVE

	Condition patientAtLoc(OP_LAYOUT_TYPE_OAOAB, OPER_TYPE_EQUAL);
	
	patientAtLoc[0] = *_patient;
	patientAtLoc[0].attrib = ATTRIB_TYPE_ROOM;
	
	patientAtLoc[1] = *_locative;
	patientAtLoc[1].attrib = ATTRIB_TYPE_ROOM;
	
	m_preconds->AddCondition(patientAtLoc);
}

std::string Bludgeon::Express(Agent* agent, Room* room)
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
	str << _agent << " hit " << _patient << " in the head with " << _instrument;
	return str.str();
}

Bludgeon::operator std::string()
{
	return "Bludgeon";
}

int Bludgeon::Cost(RoomManager* rm)
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