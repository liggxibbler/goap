#include "Room.h"
#include "Object.h"
#include "Agent.h"

using namespace GOAP;

int Room::s_nextID = 0;

Room::Room() : m_ID(s_nextID++)
{
	SetRoom(this);
}

Room::Room(const Room& other) : m_ID(s_nextID++)
{
	SetRoom(this);
}

Room::Room(std::string name , RoomName rn) : Object(name), m_type(rn), m_ID(s_nextID++)
{
	SetRoom(this);
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


std::set<Agent*>::iterator Room::GetFirstAgent()
{
	return m_agents.begin();
}

std::set<Agent*>::iterator Room::GetLastAgent()
{
	return m_agents.end();
}

Agent* Room::AddAgent(std::string name)
{
	Agent* agent = new Agent(name);
	m_agents.insert(agent);
	agent->SetRoom(this);
	agent->See(this);
	return agent;
}

void Room::AddAgent(Agent* agent)
{
	m_agents.insert(agent);
	agent->SetRoom(this);
}

RoomName Room::GetType()
{
	return m_type;
}

bool Room::Update(World* world, int turn)
{
	bool result = false;
	bool murder = false;

	for(auto object(m_objects.begin()); object != m_objects.end(); ++object)
	{
		(*object)->Update(world, turn);
	}
	for(auto agent(m_agents.begin()); agent != m_agents.end(); ++agent)
	{
		murder = (*agent)->Update(world, turn);
		if( murder )
		{
			result = true;
			(*agent)->DoneMurder(false);
		}
	}
	
	// this deletion block copied from stackoverflow.com
	auto it = m_agents.begin();
	while(it != m_agents.end())
	{
		if (m_markedForDeletion.find(*it) != m_markedForDeletion.end())
		{
			// post-increment operator returns a copy, then increment
			m_agents.erase(it++);
		}
		else
		{
			// pre-increment operator increments, then return
			++it;
		}
	}

	return result;
}

void Room::MarkForDeletion(Agent* agent)
{
	m_markedForDeletion.insert(agent);
}