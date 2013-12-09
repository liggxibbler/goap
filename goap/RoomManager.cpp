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

void RoomManager::Initialize(std::vector<Agent*>::iterator first, std::vector<Agent*>::iterator last)
{
	Agent* agent = NULL;
	
	Room* kitchen = new Room("Kitchen", ROOM_KITCHEN, 0);
	m_mapRoom[ROOM_KITCHEN] = kitchen;
	m_rooms.push_back(kitchen);

	Room* dining = new Room("Dining Room", ROOM_DINING_ROOM, 0);
	m_mapRoom[ROOM_DINING_ROOM] = dining;
	m_rooms.push_back(dining);

	Room* living = new Room("Living Room", ROOM_LIVING_ROOM, 0);
	m_mapRoom[ROOM_LIVING_ROOM] = living;
	m_rooms.push_back(living);

	Room* bath = new Room("Bathroom", ROOM_BATHROOM, 0);
	m_mapRoom[ROOM_BATHROOM] = bath;
	m_rooms.push_back(bath);

	// get list of agents, make new room for each
	Room* room = NULL;
	for(auto iter = first; iter != last; ++iter)
	{
		agent = *iter;
		std::string roomName(agent->GetName() + std::string("'s bedroom"));
		room = new Room(roomName, ROOM_BEDROOM, agent);
		m_mapBedroom[agent] = room;
		m_rooms.push_back(room);
		agent->See(room, false);
		agent->See(kitchen, false);
		agent->See(dining, false);
		agent->See(living, false);
		agent->See(bath, false);
	}
}

Room* RoomManager::GetRoom(RoomName rn, Agent* agent)
{
	if(rn == ROOM_BEDROOM)
	{
		if (agent == NULL)
		{
			return NULL;
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

std::list<Room*>::iterator RoomManager::GetFirstRoom()
{
	return m_rooms.begin();
}

std::list<Room*>::iterator RoomManager::GetLastRoom()
{
	return m_rooms.end();
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