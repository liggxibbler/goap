#include "Strangle.h"
#include "RoomManager.h"

using namespace GOAP;

Strangle::Strangle()
{
}

Strangle::Strangle(const Strangle& other)
{
}

Strangle::~Strangle()
{
}

Strangle::operator ActionType()
{
	return ACTION_STRANGLE;
}

Strangle* Strangle::Clone()
{
	Strangle* newStrangle = new Strangle();
	newStrangle->CloneData(this);
	return newStrangle;
}

void Strangle::InitArgs()
{
	Murder::InitArgs();

	ConditionParameter inst;
	
	//INSTRUMENT
	inst.semantic = SEMANTIC_ROLE_INSTRUMENT;
	inst.instance = NULL;
	inst.type = OBJ_TYPE_SQUEEZER | OBJ_TYPE_OBJECT;
	inst.strict = true;
	m_args.push_back(inst);
}

std::string Strangle::Express(Agent* agent, Room* room)
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
	str << _agent << " strangled " << _patient << " with " << _instrument;
	return str.str();
}

Strangle::operator std::string()
{
	return "Strangle";
}
