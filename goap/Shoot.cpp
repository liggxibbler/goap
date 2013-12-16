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
	return ACTION_SHOOT;
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

	ConditionParameter inst;

	//INSTRUMENT
	inst.semantic = SEMANTIC_ROLE_INSTRUMENT;
	inst.instance = NULL;
	inst.type = OBJ_TYPE_PROJECTILE | OBJ_TYPE_OBJECT | OBJ_TYPE_PROP;
	inst.strict = true;
	m_args.push_back(inst);
}

std::string Shoot::Express(Agent* agent, Room* room)
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
	str << _agent << " shot " << _patient << " with " << _instrument;
	return str.str();
}

Shoot::operator std::string()
{
	return "Shoot";
}