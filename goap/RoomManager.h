#ifndef _GOAP_ROOMMANAGER_H_
#define _GOAP_ROOMMANAGER_H_

#include <map>
#include "Common.h"
#include <vector>
#include <list>

namespace GOAP
{
	class Room;
	class Agent;

	class RoomManager
		{
			RoomManager();
			RoomManager(const RoomManager& other);
			~RoomManager();
		
		public:
			
			static RoomManager* Instance();
			void Initialize(/*std::vector<Agent*>::iterator first, std::vector<Agent*>::iterator last*/); // get list of agents, make new room for each
			
			Room* GetRoom(int id);
			Room* GetRoom(std::string name);
			Room* GetRoom(RoomName rn, Agent* agent = NULL);

			Room* GetRandomRoom(Agent* agent);

			std::list<Room*>::iterator GetFirstRoom();
			std::list<Room*>::iterator GetLastRoom();

			void ShowBedrooms( Agent* murderer );

			void AddAgentProbabilities(Agent* agent);

			float GetProb(Agent* agent, Room* room);
			float GetProbOthers(Agent* agent, Room* room);
			float GetProbAlone(Agent* agent, Room* room);
			float GetProbWillBeFound(Agent* agent, Room* room);

			void ClearRooms();

			void ShowEverything(Agent* seer);

		private:
			std::map<RoomName, Room*> m_mapRoom;
			std::map<Agent*, Room*> m_mapBedroom;
			std::list<Room*> m_rooms;
			std::map< Agent*, std::map<Room*, float> > m_probabilities;
	};
}

#endif