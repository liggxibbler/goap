#include "Shoot.h"
#include "RoomManager.h"

using namespace GOAP;

Shoot::Shoot()
{
}

Shoot::Shoot(const Shoot& other)
{
}

Shoot::~Shoot()
{
}

Shoot::operator ActionType()
{
	return ActionType::SHOOT;
}

Shoot* Shoot::Clone()
{
	Shoot* newShoot = new Shoot();
	newShoot->CloneData(this);
	return newShoot;
}

void Shoot::InitArgs()
{
	Murder::InitArgs();

	Argument inst;

	//INSTRUMENT
	inst.semantic = SemanticRole::INSTRUMENT;
	inst.instance = nullptr;
	inst.type = ObjectType::PROJECTILE | ObjectType::OBJECT | ObjectType::PROP;
	inst.strict = true;
	m_args.push_back(inst);
}

std::string Shoot::Express(const Agent* agent, const Room* room) const
{
	auto sub = GetArg(SemanticRole::AGENT);
	auto obj = GetArg(SemanticRole::PATIENT);
	auto ins = GetArg(SemanticRole::INSTRUMENT);

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
	str << _agent << " shot " << _patient << " with " << _instrument;
	return str.str();
}

std::string Shoot::GetName() const
{
	return "Shoot";
}