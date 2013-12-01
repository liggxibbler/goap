#include "World.h"
#include "Room.h"

using namespace GOAP;


World::World()
{
}

World::World(const World& other)
{
}

World::~World()
{
}


Room* World::AddRoom(std::string name, RoomName rn)
{
	Room* room = new Room(name, rn);
	m_rooms.push_back(room);
	return room;
}

void World::AddRoom(Room* room)
{
	m_rooms.push_back(room);
}


Room* World::GetRoom(std::string name)
{
	return 0;
}


World* World::Clone()
{
	return 0;
}


std::string World::GetName()
{
	return m_name;
}


std::list<Room*>::iterator World::GetFirstRoom()
{
	return m_rooms.begin();
}

std::list<Room*>::iterator World::GetLastRoom()
{
	return m_rooms.end();
}

Room* World::GetRandomRoom()
{
	int i = rand() % m_rooms.size();
	auto room = m_rooms.begin();
	for(int j = 0; j < i; j++)
	{
		room++;
	}
	return *room;
}