#ifndef _GOAP_WORLD_H_
#define _GOAP_WORLD_H_

#include <map>
#include <string>

namespace GOAP
{
	class Room;

	class World
	{
	public:
		World();
		World(const World& other);
		~World();

		Room* AddRoom(std::string name);
		void AddRoom(Room* room);

		Room* GetRoom(std::string name);

		World* Clone();

		std::string GetName();
		
	private:
		std::map<std::string, Room*> m_rooms;
		std::string name;
	};
}

#endif