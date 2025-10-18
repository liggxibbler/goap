#include "Shoot.h"
#include "Room.h"

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

ActionType Shoot::GetActionType() const
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
	str << "[" << GetRoomDisplayName(room) << "] " << _agent << " shot " << _patient << " with " << _instrument;
	return str.str();
}

std::string Shoot::GetName() const
{
	return "Shoot";
}