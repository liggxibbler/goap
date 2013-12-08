#ifndef _GOAP_WORLD_H_
#define _GOAP_WORLD_H_

#include <list>
#include <string>
#include "Common.h"
#include "RoomManager.h"

namespace GOAP
{
	class World
	{
	public:
		World();
		World(const World& other);
		~World();

		/*Room* AddRoom(std::string name, RoomName rn);
		void AddRoom(Room* room);*/

		Room* GetRoom(std::string name);
		Room* GetRoom(int id);
		Room* GetRoom(RoomName rn);
		Room* GetRandomRoom(Agent* agent);

		World* Clone();

		std::string GetName();
		
		std::list<Room*>::iterator GetFirstRoom();
		std::list<Room*>::iterator GetLastRoom();

	private:
		//std::list<Room*> m_rooms;
		RoomManager* m_roomManager;
		std::string m_name;
	};
}

#endif