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

Bludgeon::operator ActionType()
{
	return ActionType::BLUDGEON;
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

	Argument inst;
	
	//INSTRUMENT
	inst.semantic = SemanticRole::INSTRUMENT;
	inst.instance = nullptr;
	inst.type = ObjectType::BLUNT | ObjectType::OBJECT | ObjectType::PROP;
	inst.strict = true;
	m_args.push_back(inst);
}

std::string Bludgeon::Express(const Agent* agent, const Room* room) const
{
	auto sub = GetArg(SemanticRole::AGENT);
	auto obj = GetArg(SemanticRole::PATIENT);
	auto ins = GetArg(SemanticRole::INSTRUMENT);

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