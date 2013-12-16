#include "Stab.h"
#include "RoomManager.h"

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
	Murder::InitArgs();

	ConditionParameter inst;

	// INSTRUMENT
	inst.semantic = SEMANTIC_ROLE_INSTRUMENT;
	inst.instance = NULL;
	inst.type = OBJ_TYPE_BLADE | OBJ_TYPE_OBJECT | OBJ_TYPE_PROP;
	inst.strict = true;
	m_args.push_back(inst);
}

std::string Stab::Express(Agent* agent, Room* room)
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
	str << _agent << " stabbed " << _patient << " with " << _instrument;
	return str.str();
}

Stab::operator std::string()
{
	return "Stab";
}
