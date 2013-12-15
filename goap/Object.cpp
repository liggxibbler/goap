#include "Object.h"
#include "Room.h"
#include "RoomManager.h"
#include "OperatorManager.h"

using namespace GOAP;

int Object::s_numObjects = 1;

Object::Object() : m_canBeFoundIn(0), m_bearer(0)
{
	InitAttribMap();

	m_owner = NULL;
	m_name = "ANONYMOUS";
	m_id = s_numObjects++;
}


Object::Object(std::string name, Object* owner) : m_canBeFoundIn(0), m_bearer(0)
{
	InitAttribMap();

	m_owner = owner;
	m_name = name;
	m_id = s_numObjects++;
}

Object::Object(const Object& other)
{
	m_owner = other.m_owner;
	m_bearer = other.m_bearer;
	m_name = other.m_name;
	m_id = other.m_id;
	m_canBeFoundIn = other.m_canBeFoundIn;

	m_attribs[ATTRIBUTE_POSX] = &m_posx;
	m_attribs[ATTRIBUTE_POSY] = &m_posy;
	m_attribs[ATTRIBUTE_ROOM] = &m_room;
}

Object::~Object()
{
	// TBI
}


int Object::GetAttrib(AttributeType at)
{
	return *m_attribs[at];
}

void Object::SetAttribute(AttributeType at, int val)
{
	*m_attribs[at] = val;
}

Object::operator GOAP::ObjectType()
{
	return OBJ_TYPE_OBJECT;
}

int& Object::operator[] (AttributeType at)
{
	return *m_attribs[at];
}

int Object::GetID()
{
	return m_id;
}

Object* Object::GetOwner()
{
	return m_owner;
}

std::string Object::GetName()
{
	return m_name;
}

int Object::GetCompoundType()
{
	return OBJ_TYPE_OBJECT;
}

bool Object::Update(Op::OperatorManager* om, RoomManager* rm, int turn)
{
	if(m_owner != NULL)
	{
		// set my position to my parent's position
		SetRoom(m_owner->GetRoom());
	}
	return true;
}

void Object::Examine()
{
}

void Object::MayBeFoundIn(int rooms)
{
	m_canBeFoundIn |= rooms;
}

bool Object::CanBeMurderWeapon()
{
	return false;
}

void Object::SetRoom(Room* room)
{
	m_roomInstance = room;
	if(room != 0)
	{
	    m_room = room->GetID();
	}
	else
	{
	    m_room = 0;
	}
}

Room* Object::GetRoom()
{
	return m_roomInstance;
}

Object* Object::Clone()
{
	return new Object(*this);
}

void Object::SetOwner(Object* owner)
{
	m_owner = owner;
}

Object* Object::GetBearer()
{
	return m_bearer;
}
void Object::SetBearer(Object* bearer)
{
	m_bearer = bearer;
}

void Object::InitAttribMap()
{
	m_attribs[ATTRIBUTE_POSX]	= &m_posx;
	m_attribs[ATTRIBUTE_POSY]	= &m_posy;
	m_attribs[ATTRIBUTE_ROOM]	= &m_room;
	m_attribs[ATTRIBUTE_ID]		= &m_id;
}
