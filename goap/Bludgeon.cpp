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
	Murder::InitArgs();

	ConditionParameter inst;
	
	//INSTRUMENT
	inst.semantic = SEMANTIC_ROLE_INSTRUMENT;
	inst.instance = NULL;
	inst.type = OBJ_TYPE_BLUNT | OBJ_TYPE_OBJECT;
	inst.strict = true;
	m_args.push_back(inst);
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