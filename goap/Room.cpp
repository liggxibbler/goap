#include "Room.h"
#include "Object.h"
#include "Agent.h"

using namespace GOAP;

int Room::s_nextID = 0;

Room::Room() : m_ID(s_nextID++), m_numAgents(0)
{
	SetRoom(this);
}

Room::Room(const Room& other) : m_ID(s_nextID++)
{
	SetRoom(this);
}

Room::Room(std::string name , RoomName rn, Object* owner) : Object(name, owner), m_type(rn), m_ID(s_nextID++), m_numAgents(0)
{
	SetRoom(this);
	m_attribs[ATTRIB_TYPE_NUM_AGENTS] = &m_numAgents;
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


//std::string Room::GetName()
//{
//	return m_name;
//}

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
	m_numAgents++;
	return agent;
}

void Room::AddAgent(Agent* agent)
{
	m_agents.insert(agent);
	agent->SetRoom(this);
	agent->See(this);
	m_numAgents++;
}

RoomName Room::GetType()
{
	return m_type;
}

bool Room::Update(Op::OperatorManager* om, RoomManager* rm, int turn)
{
	bool result = false;
	bool murder = false;

	DUMP("*** Updating room " << m_name << " at turn " << turn << " ***")

	for(auto object(m_objects.begin()); object != m_objects.end(); ++object)
	{
		(*object)->Update(om, rm, turn);
	}
	for(auto agent(m_agents.begin()); agent != m_agents.end(); ++agent)
	{
		DUMP("    ** Updating agent " << (*agent)->GetName() << " at turn " << turn)
		murder = (*agent)->Update(om, rm, turn);
		if( murder )
		{
			result = true;
			(*agent)->DoneMurder(false);
		}
	}

	return result;
}

void Room::MarkForDeletion(Agent* agent)
{
	m_markedForDeletion.insert(agent);
}

void Room::MarkForAddition(Agent* agent)
{
	m_markedForAddition.insert(agent);
}

void Room::UpdateAgentPositions()
{
	auto addIter = m_markedForAddition.begin();
	while(addIter != m_markedForAddition.end())
	{
		AddAgent(*(addIter++));
		m_numAgents++;
	}

	auto delIter = m_agents.begin();
	while(delIter != m_agents.end())
	{
		if (m_markedForDeletion.find(*delIter) != m_markedForDeletion.end())
		{
			// post-increment operator returns a copy, then increment
			m_agents.erase(delIter++);
			m_numAgents--;
		}
		else
		{
			// pre-increment operator increments, then return
			++delIter;
		}
	}

	m_markedForAddition.clear();
	m_markedForDeletion.clear();
}

Object* Room::Clone()
{
	return new Room(*this);
}

int Room::GetCompoundType()
{
	return OBJ_TYPE_OBJECT | OBJ_TYPE_ROOM;
}