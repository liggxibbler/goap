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

Room* RoomManager::GetRoom(RoomName rn, Agent* agent) const
{
	if(rn == RoomName::BEDROOM)
	{
		if (agent == nullptr)
		{
			return nullptr;
		}

		return m_mapBedroom.at(agent);
	}
	else
	{
		return m_mapRoom.at(rn);
	}
}

Room* RoomManager::GetRandomRoom(Agent* agent) const
{
	int rnd = rand() % 5;
	int room = 1 << rnd; // left bit shift, to the rnd'th power of two
	return GetRoom((RoomName)room, agent);
}

const std::list<Room*>& GOAP::RoomManager::GetRooms() const
{
	return m_rooms;
}

void GOAP::RoomManager::CreateRoomFor(Agent* agent)
{
	Room* room = new Room(agent->GetName() + std::string("'s bedroom"), RoomName::BEDROOM, agent);
	m_mapBedroom[agent] = room;
	m_rooms.push_back(room);
}

Room* RoomManager::GetRoom(std::string name) const
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

Room* RoomManager::GetRoom(int id) const
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

void RoomManager::ShowBedrooms(Agent* murderer) const
{
	for(auto room(m_mapBedroom.begin()); room != m_mapBedroom.end(); ++room)
	{
		murderer->See(room->second, false);
	}
}

void GOAP::RoomManager::ShowCommonRooms(Agent* agent) const
{
	agent->See(m_mapRoom.at(RoomName::KITCHEN), false);
	agent->See(m_mapRoom.at(RoomName::LIVING_ROOM), false);
	agent->See(m_mapRoom.at(RoomName::DINING_ROOM), false);
	agent->See(m_mapRoom.at(RoomName::BATHROOM), false);
}

void GOAP::RoomManager::ShowOwnBedroom(Agent* agent) const
{
	agent->See(m_mapBedroom.at(agent), false);
}

void RoomManager::AddAgentProbabilities(Agent* agent)
{
	const float* prob = agent->GetProbabilities();

	m_probabilities[agent][m_mapRoom.at(RoomName::KITCHEN)] = prob[0];
	m_probabilities[agent][m_mapRoom.at(RoomName::LIVING_ROOM)] = prob[1];
	m_probabilities[agent][m_mapRoom.at(RoomName::DINING_ROOM)] = prob[2];
	m_probabilities[agent][m_mapRoom.at(RoomName::BATHROOM)] = prob[3];
	m_probabilities[agent][m_mapBedroom.at(agent)] = prob[4];
}

float RoomManager::GetProb(Agent* agent, Room* room) const
{
	if( m_probabilities.at(agent).find(room) == m_probabilities.at(agent).end() )
	{
		return 0.0f;
	}
	
	//DUMP("% P of " << agent->GetName() << " at " << room->GetName() << " is " << m_probabilities[agent][room] / 100.0f << " %")

	return m_probabilities.at(agent).at(room) / 100.0f;
}

float RoomManager::GetProbOthers(Agent* agent, Room* room) const
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
float RoomManager::GetProbAlone(Agent* agent, Room* room) const
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
float RoomManager::GetProbWillBeFound(Agent* agent, Room* room) const
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

void GOAP::RoomManager::UpdateAllRooms() const
{
	for (Room* room : m_rooms)
	{
		room->UpdateAgentPositions();
	}
}

void RoomManager::ShowEverything(Agent* seer) const
{
	for(Room* room : m_rooms)
	{
		seer->See(room, true);
	}
}