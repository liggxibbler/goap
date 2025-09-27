#include "RoomManager.h"
#include "Agent.h"
#include "Room.h"
#include <string>

using namespace GOAP;

RoomManager::RoomManager()
{
}

RoomManager::RoomManager(const RoomManager& other)
{
}

RoomManager::~RoomManager()
{
}

RoomManager* RoomManager::Instance()
{
	static RoomManager rm;
	return &rm;
}

void RoomManager::Initialize(/*std::vector<Agent*>::iterator first, std::vector<Agent*>::iterator last*/)
{
	Agent* agent = nullptr;
	
	Room* kitchen = new Room("The Kitchen", RoomName::KITCHEN, 0);
	m_mapRoom[RoomName::KITCHEN] = kitchen;
	m_rooms.push_back(kitchen);

	Room* dining = new Room("The Dining Room", RoomName::DINING_ROOM, 0);
	m_mapRoom[RoomName::DINING_ROOM] = dining;
	m_rooms.push_back(dining);

	Room* living = new Room("The Living Room", RoomName::LIVING_ROOM, 0);
	m_mapRoom[RoomName::LIVING_ROOM] = living;
	m_rooms.push_back(living);

	Room* bath = new Room("The Bathroom", RoomName::BATHROOM, 0);
	m_mapRoom[RoomName::BATHROOM] = bath;
	m_rooms.push_back(bath);

	// get list of agents, make new room for each
	/*Room* room = nullptr;
	for(auto iter = first; iter != last; ++iter)
	{
		agent = *iter;
		std::string roomName(agent->GetName() + std::string("'s bedroom"));
		room = new Room(roomName, RoomName::BEDROOM, agent);
		m_mapBedroom[agent] = room;
		m_rooms.push_back(room);
		agent->See(room, false);
		agent->See(kitchen, false);
		agent->See(dining, false);
		agent->See(living, false);
		agent->See(bath, false);
	}*/
}

Room* RoomManager::GetRoom(RoomName rn, Agent* agent)
{
	if(rn == RoomName::BEDROOM)
	{
		if (agent == nullptr)
		{
			return nullptr;
		}

		return m_mapBedroom[agent];
	}
	else
	{
		return m_mapRoom[rn];
	}
}

Room* RoomManager::GetRandomRoom(Agent* agent)
{
	int rnd = rand() % 5;
	int room = 1 << rnd; // left bit shift, to the rnd'th power of two
	return GetRoom((RoomName)room, agent);
}

const std::list<Room*>& GOAP::RoomManager::GetRooms()
{
	return m_rooms;
}

Room* RoomManager::GetRoom(std::string name)
{
	for(auto room(m_rooms.begin()); room != m_rooms.end(); ++room)
	{
		if ((*room)->GetName() == name)
		{
			return *room;
		}
	}
	return 0;
}

Room* RoomManager::GetRoom(int id)
{
	for(auto room(m_rooms.begin()); room != m_rooms.end(); ++room)
	{
		if ((*room)->GetID() == id)
		{
			return *room;
		}
	}
	return 0;
}

void RoomManager::ShowBedrooms(Agent* murderer)
{
	for(auto room(m_mapBedroom.begin()); room != m_mapBedroom.end(); ++room)
	{
		murderer->See(room->second, false);
	}
}

void RoomManager::AddAgentProbabilities(Agent* agent)
{
	int* prob = agent->GetProbabilities();
	Room* room = nullptr;
	std::string roomName(agent->GetName() + std::string("'s bedroom"));
	room = new Room(roomName, RoomName::BEDROOM, agent);
	m_mapBedroom[agent] = room;
	m_rooms.push_back(room);
	
	agent->See(room, false);
	agent->See(m_mapRoom[RoomName::KITCHEN], false);
	agent->See(m_mapRoom[RoomName::LIVING_ROOM], false);
	agent->See(m_mapRoom[RoomName::DINING_ROOM], false);
	agent->See(m_mapRoom[RoomName::BATHROOM], false);

	m_probabilities[agent][m_mapRoom[RoomName::KITCHEN]] = prob[0];
	m_probabilities[agent][m_mapRoom[RoomName::LIVING_ROOM]] = prob[1];
	m_probabilities[agent][m_mapRoom[RoomName::DINING_ROOM]] = prob[2];
	m_probabilities[agent][m_mapRoom[RoomName::BATHROOM]] = prob[3];
	m_probabilities[agent][room] = prob[4];
}

float RoomManager::GetProb(Agent* agent, Room* room)
{
	if( m_probabilities[agent].find(room) == m_probabilities[agent].end() )
	{
		m_probabilities[agent][room] = 0;
	}
	
	//DUMP("% P of " << agent->GetName() << " at " << room->GetName() << " is " << m_probabilities[agent][room] / 100.0f << " %")

	return m_probabilities[agent][room] / 100.0f;
}

float RoomManager::GetProbOthers(Agent* agent, Room* room)
{
	float prob = 1.0f;
	for(auto record(m_probabilities.begin()); record != m_probabilities.end(); ++record)
	{
		if(record->first != agent)
		{
			prob *= GetProb(record->first, room) / 100.0f;
		}
	}
	return prob;
}
float RoomManager::GetProbAlone(Agent* agent, Room* room)
{
	float prob = 1.0f;
	prob *= GetProb(agent, room);
	for(auto record(m_probabilities.begin()); record != m_probabilities.end(); ++record)
	{
		if(record->first != agent)
		{
			prob *= (1.0f - GetProb(record->first, room) / 100.0f);
		}
	}
	return prob;
}
float RoomManager::GetProbWillBeFound(Agent* agent, Room* room)
{
	float prob = 1.0f;
	for(auto record(m_probabilities.begin()); record != m_probabilities.end(); ++record)
	{
		if(record->first != agent)
		{
			prob *= (1.0f - GetProb(record->first, room) / 100.0f);
		}
	}
	return 1.0f - prob;
}

void RoomManager::ClearRooms()
{
	/*for(bedroom)
	{
		for(agent)
		{
			wipe agent's room';
			remove agent from list;
		}
	}
	for(otherrooms)
	{
		for(agent)
		{
			wipe agent's room';
			remove agent from list;
		}
	}*/
}

void RoomManager::ShowEverything(Agent* seer)
{
	for(auto room(m_rooms.begin()); room != m_rooms.end(); ++room)
	{
		seer->See(*room, true);
	}
}