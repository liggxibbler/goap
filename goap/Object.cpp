#include "Object.h"
#include "Room.h"
#include "World.h"

using namespace GOAP;

int Object::s_numObjects = 0;

Object::Object() : m_canBeFoundIn(0)
{
	m_attribs[ATTRIB_TYPE_POSX] = &m_posx;
	m_attribs[ATTRIB_TYPE_POSY] = &m_posy;
	m_attribs[ATTRIB_TYPE_ROOM] = &m_room;
	
	m_owner = NULL;
	m_name = "ANONYMOUS";
	m_id = s_numObjects++;
}


Object::Object(std::string name, Object* owner) : m_canBeFoundIn(0)
{
	m_attribs[ATTRIB_TYPE_POSX] = &m_posx;
	m_attribs[ATTRIB_TYPE_POSY] = &m_posy;
	m_attribs[ATTRIB_TYPE_ROOM] = &m_room;
	m_owner = owner;
	m_name = name;
	m_id = s_numObjects++;
}

Object::Object(const Object& other) : m_canBeFoundIn(0)
{
	// TBI
}

Object::~Object()
{
	// TBI
}
	
		
int Object::GetAttrib(AttributeType at)
{
	return *m_attribs[at];
}

void Object::SetAttrib(AttributeType at, int val)
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

void Object::Update(World* world, int turn)
{
	if(m_owner != NULL)
	{
		// set my position to my parent's position
		SetRoom(m_owner->GetRoom());
	}
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
	m_room = room->GetID();
}

Room* Object::GetRoom()
{
	return m_roomInstance;
}