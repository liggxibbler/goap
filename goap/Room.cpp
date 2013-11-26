#include "Room.h"
#include "Object.h"
#include "Agent.h"

using namespace GOAP;

Room::Room()
{
}

Room::Room(const Room& other)
{
}

Room::Room(std::string name) : m_name(name)
{
}

Room::~Room()
{
}


void Room::SetLeft(Room* left)
{
	m_left = left;
}

void Room::SetRight(Room* right)
{
	m_right = right;
}

Room* Room::GetLeft()
{
	return m_left;
}

Room* Room::GetRight()
{
	return m_right;
}


Object* Room::AddObject(std::string name)
{
	Object* obj = new Object(name);
	m_objects.push_back(obj);
	return obj;
}

void Room::AddObject(Object* obj)
{
	m_objects.push_back(obj);
}


std::string Room::GetName()
{
	return m_name;
}


Room* Room::Clone()
{
	return 0;
}


std::list<Object*>::iterator Room::GetFirstObject()
{
	return m_objects.begin();
}

std::list<Object*>::iterator Room::GetLastObject()
{
	return m_objects.end();
}


std::list<Agent*>::iterator Room::GetFirstAgent()
{
	return m_agents.begin();
}

std::list<Agent*>::iterator Room::GetLastAgent()
{
	return m_agents.end();
}