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
	return ActionType::STAB;
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

	Argument inst;

	// INSTRUMENT
	inst.semantic = SemanticRole::INSTRUMENT;
	inst.instance = nullptr;
	inst.type = ObjectType::BLADE | ObjectType::OBJECT | ObjectType::PROP;
	inst.strict = true;
	m_args.push_back(inst);
}

std::string Stab::Express(const Agent* agent, const Room* room) const
{
	const Argument& sub = GetArg(SemanticRole::AGENT);
	const Argument& obj = GetArg(SemanticRole::PATIENT);
	const Argument& ins = GetArg(SemanticRole::INSTRUMENT);

	std::string _agent;
	std::string _patient;
	std::string _instrument(ins.instance->GetName());

	if(sub.instance == agent)
	{
		_agent = "I";
	}
	else
	{
		_agent = sub.instance->GetName();
	}

	if(obj.instance == agent)
	{
		_patient = "me";
	}
	else
	{
		_patient = obj.instance->GetName();
	}

	std::stringstream str;
	str << _agent << " stabbed " << _patient << " with " << _instrument;
	return str.str();
}

std::string Stab::GetName() const
{
	return "Stab";
}
