#include "Room.h"
#include "Object.h"
#include "Agent.h"

using namespace GOAP;

Room::Room() : Object(), m_numAgents(0), m_isMurderRoom(false)
{
	m_room = m_id;
	m_roomInstance = this;
}

Room::Room(const Room& other)
{
	m_room = m_id;
	m_name = other.m_name;
	m_roomInstance = this;
	for(auto prop(other.m_objects.begin()); prop != other.m_objects.end(); ++prop)
	{
		m_objects.insert(*prop);
	}
	for(auto agent(other.m_agents.begin()); agent != other.m_agents.end(); ++agent)
	{
		m_agents.insert(*agent);
	}
}

Room::Room(std::string&& name , RoomName rn, Object* owner) :
Object(name, owner), m_type(rn), m_numAgents(0), m_isMurderRoom(false)
{
	m_room = m_id;
	m_roomInstance = this;
	m_attribs[AttributeType::NUM_AGENTS] = &m_numAgents;
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

Prop* Room::AddObject(std::string name)
{
	Prop* obj = new Prop(name);
	m_objects.insert(obj);
	obj->SetRoom(this);
	return obj;
}

void Room::AddObject(Prop* obj)
{
	if(obj->GetRoom() != 0)
	{
		obj->GetRoom()->RemoveObject(obj);
	}
	m_objects.insert(obj);
	obj->SetRoom(this);
}


//std::string Room::GetName()
//{
//	return m_name;
//}

const std::set<Prop*>& GOAP::Room::GetObjects()
{
	return m_objects;
}

const std::set<Agent*>& GOAP::Room::GetAgents()
{
	return m_agents;
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

bool Room::Update(const Op::OperatorManager& om, const RoomManager& rm, int turn)
{
	//m_murder = false;

	DUMP("*** Updating room " << m_name << " at turn " << turn << " ***")

	for(auto object(m_objects.begin()); object != m_objects.end(); ++object)
	{
		(*object)->Update(om, rm, turn);
	}

	for(auto agent(m_agents.begin()); agent != m_agents.end(); ++agent)
	{
		DUMP("    ** Updating agent " << (*agent)->GetName() << " at turn " << turn)
		if( (*agent)->Update(om, rm, turn) )
		{
			m_isMurderRoom = true;
			//(*agent)->DoneMurder(false);
		}
	}

	return m_isMurderRoom;
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
		if((*(*addIter))[AttributeType::ALIVE] != false)
		{
			AddAgent(*(addIter++));
			m_numAgents++;
		}
		else
		{
			++addIter;
		}
	}

	auto delIter = m_agents.begin();
	while(delIter != m_agents.end())
	{

		if (m_markedForDeletion.find(*delIter) != m_markedForDeletion.end())
		{
			// post-increment operator returns a copy, then increment
			if((*(*delIter))[AttributeType::ALIVE] != false)
			{
				m_agents.erase(delIter++);
				m_numAgents--;
			}
			else
			{
				++delIter;
			}
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

bool GOAP::Room::ContainsAnyExcept(const std::list<Agent*>& toExclude)
{	
	for (Agent* agent : m_agents)
	{
		for (Agent* excludee : toExclude)
		{
			if (agent != excludee)
			{
				return true;
			}
		}
	}
	return false;
}

bool GOAP::Room::ContainsMurderWitness(const std::list<Agent*>& toExclude)
{
	if (!m_isMurderRoom)
		return false;

	return ContainsAnyExcept(toExclude);
}

Object* Room::Clone()
{
	return new Room(*this);
}

ObjectType Room::GetCompoundType()
{
	return ObjectType::OBJECT | ObjectType::ROOM;
}

bool Room::GetMurder()
{
	return m_isMurderRoom;
}

void Room::RemoveObject(Prop* obj)
{
	auto remove(m_objects.begin());
	while( remove != m_objects.end() )
	{
		if(*remove == obj)
		{
			m_objects.erase(remove++);
		}
		else
		{
			++remove;
		}
	}
	obj->SetRoom(0);
}

void Room::ResetAgentUpdateFlags()
{
	for(auto agent(m_agents.begin()); agent != m_agents.end(); ++agent)
	{
		(*agent)->ResetUpdateFlag();
	}
}

//Room::operator ObjectType ()
//{
//	return ObjectType::ROOM;
//}

void Room::Examine()
{
}