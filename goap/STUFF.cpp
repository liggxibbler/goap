#include "STUFF.h"

using namespace GOAP;

STUFF::STUFF(std::string name, Object* owner) : Object(name, owner), m_canBeFoundIn(0), m_bearer(0)
{
}

STUFF::STUFF() : Object(), m_canBeFoundIn(0), m_bearer(0)
{
}

STUFF::STUFF(const STUFF& other) : Object(other)
{
	m_owner = other.m_owner;
	m_bearer = other.m_bearer;
	m_canBeFoundIn = other.m_canBeFoundIn;

	InitAttribMap();
}

STUFF::~STUFF()
{
}

Object* STUFF::GetBearer()
{
	return m_bearer;
}
void STUFF::SetBearer(Object* bearer)
{
	m_bearer = bearer;
}

Object* STUFF::Clone()
{
	return new STUFF(*this);
}

bool STUFF::CanBeMurderWeapon()
{
	return false;
}

void STUFF::MayBeFoundIn(int rooms)
{
	m_canBeFoundIn |= rooms;
}

bool STUFF::Update(Op::OperatorManager* om, RoomManager* rm, int turn)
{
	if(m_bearer != 0)
	{
		SetRoom(m_bearer->GetRoom());
	}		
	
	return true;
}

int STUFF::GetCompoundType()
{
	return OBJ_TYPE_STUFF;
}

STUFF::operator GOAP::ObjectType()
{
	return OBJ_TYPE_OBJECT;
}

void STUFF::InitAttribMap()
{
}

void STUFF::Examine()
{
}