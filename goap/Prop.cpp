#include "Prop.h"

using namespace GOAP;

int Prop::s_value = 0;
int Prop::s_numInstances = 0;

Prop::Prop(std::string name, Object* owner) : Object(name, owner), m_bearer(0), m_bearerID(0)
{
	++s_numInstances;
	InitAttribMap();
}

Prop::Prop() : Object(), m_bearer(0), m_bearerID(0)
{
	++s_numInstances;
	InitAttribMap();
}

Prop::Prop(const Prop& other) : Object(other)
{
	m_owner = other.m_owner;
	m_bearer = other.m_bearer;
	m_canBeFoundIn = other.m_canBeFoundIn;

	InitAttribMap();
}

Prop::~Prop()
{
}

Object* Prop::GetBearer()
{
	return m_bearer;
}
void Prop::SetBearer(Object* bearer)
{
	m_bearer = bearer;
	if(m_bearer)
	{
		m_bearerID = m_bearer->GetID();
	}
	else
	{
		m_bearerID = 0;
	}
}

Object* Prop::Clone()
{
	return new Prop(*this);
}

bool Prop::CanBeMurderWeapon()
{
	return false;
}

void Prop::MayBeFoundIn(RoomName rooms)
{
	m_canBeFoundIn = rooms;
}

bool Prop::Update(const Op::OperatorManager& om, const RoomManager& rm, int turn)
{
	if(m_bearer != 0)
	{
		SetRoom(m_bearer->GetRoom());
	}

	return true;
}

ObjectType Prop::GetCompoundType()
{
	return m_type;
}

//Prop::operator GOAP::ObjectType()
//{
//	return ObjectType::PROP;
//}

void Prop::InitAttribMap()
{
	m_attribs[AttributeType::BEARER] = &m_bearerID;
}

void Prop::Examine()
{

}

void Prop::IncreaseValue()
{
	s_value += 100;
}

int Prop::GetValue()
{
	return s_value;
}

int Prop::GetNumberOfInstances()
{
	return s_numInstances;
}

std::string Prop::GetDescription()
{
	return m_description;
}

void Prop::SetDescription(std::string desc)
{
	m_description = desc;
}

RoomName Prop::MayBeFoundIn()
{
	return m_canBeFoundIn;
}

void Prop::SetCompoundType(ObjectType type)
{
    m_type = type;
}
