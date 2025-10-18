#include "Strangle.h"
#include "RoomManager.h"
#include "Room.h"

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

ActionType Strangle::GetActionType() const
{
	return ActionType::STRANGLE;
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

	Argument inst;
	
	//INSTRUMENT
	inst.semantic = SemanticRole::INSTRUMENT;
	inst.instance = nullptr;
	inst.type = ObjectType::SQUEEZER | ObjectType::OBJECT | ObjectType::PROP;
	inst.strict = true;
	m_args.push_back(inst);
}

std::string Strangle::Express(const Agent* agent, const Room* room) const
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
	str << "[" << GetRoomDisplayName(room) << "] " << _agent << " strangled " << _patient << " with " << _instrument;
	return str.str();
}

std::string Strangle::GetName() const
{
	return "Strangle";
}
