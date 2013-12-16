#include "Prop.h"

using namespace GOAP;

Prop::Prop(std::string name, Object* owner) : Object(name, owner), m_canBeFoundIn(0), m_bearer(0)
{
	InitAttribMap();
}

Prop::Prop() : Object(), m_canBeFoundIn(0), m_bearer(0)
{
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

void Prop::MayBeFoundIn(int rooms)
{
	m_canBeFoundIn |= rooms;
}

bool Prop::Update(Op::OperatorManager* om, RoomManager* rm, int turn)
{
	if(m_bearer != 0)
	{
		SetRoom(m_bearer->GetRoom());
	}		
	
	return true;
}

int Prop::GetCompoundType()
{
	return OBJ_TYPE_OBJECT | OBJ_TYPE_PROP;
}

//Prop::operator GOAP::ObjectType()
//{
//	return OBJ_TYPE_PROP;
//}

void Prop::InitAttribMap()
{
	m_attribs[ATTRIBUTE_BEARER] = &m_bearerID;
}

void Prop::Examine()
{
}