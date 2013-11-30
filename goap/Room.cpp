#include "Room.h"
#include "Object.h"
#include "Agent.h"

using namespace GOAP;

int Room::s_nextID = 0;

Room::Room() : m_ID(s_nextID++)
{
}

Room::Room(const Room& other) : m_ID(s_nextID++)
{
}

Room::Room(std::string name , RoomName rn) : m_name(name), m_type(rn), m_ID(s_nextID++)
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

int Room::GetID()
{
	return m_ID;
}

Object* Room::AddObject(std::string name)
{
	Object* obj = new Object(name);
	m_objects.push_back(obj);
	obj->SetRoom(this);
	return obj;
}

void Room::AddObject(Object* obj)
{
	m_objects.push_back(obj);
	obj->SetRoom(this);
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

Agent* Room::AddAgent(std::string name)
{
	Agent* agent = new Agent(name);
	m_agents.push_back(agent);
	agent->SetRoom(this);
	agent->See(this);
	return agent;
}

void Room::AddAgent(Agent* agent)
{
	m_agents.push_back(agent);
	agent->SetRoom(this);
}

RoomName Room::GetType()
{
	return m_type;
}