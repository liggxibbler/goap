#include "Object.h"
#include "Room.h"
#include "RoomManager.h"
#include "OperatorManager.h"

using namespace GOAP;

int Object::s_numObjects = 1;

Object::Object() : m_roomInstance(0)
{
	InitAttribMap();

	m_owner = nullptr;
	m_name = "ANONYMOUS";
	m_id = s_numObjects++;
}


Object::Object(std::string name, Object* owner) : m_roomInstance(0)
{
	InitAttribMap();

	m_owner = owner;
	m_name = name;
	m_id = s_numObjects++;
}

Object::Object(const Object& other)
{
	m_owner = other.m_owner;
	m_name = other.m_name;
	m_id = other.m_id;

	InitAttribMap();
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

//Object::operator GOAP::ObjectType() /// XXX = 0
//{
//	return ObjectType::OBJECT;
//}

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

ObjectType Object::GetCompoundType() // XXX = 0
{
	return ObjectType::OBJECT;
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

void Object::SetOwner(Object* owner)
{
	m_owner = owner;
}

void Object::InitAttribMap()
{
	m_attribs[AttributeType::POSX]	= &m_posx;
	m_attribs[AttributeType::POSY]	= &m_posy;
	m_attribs[AttributeType::ROOM]	= &m_room;
	m_attribs[AttributeType::ID]		= &m_id;
}
