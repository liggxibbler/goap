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
		public:
			RoomManager();
			RoomManager(const RoomManager& other);
			~RoomManager();
		
			
			void Initialize(/*std::vector<Agent*>::iterator first, std::vector<Agent*>::iterator last*/); // get list of agents, make new room for each
			
			Room* GetRoom(int id) const;
			Room* GetRoom(std::string name) const;
			Room* GetRoom(RoomName rn, Agent* agent = nullptr) const;

			Room* GetRandomRoom(Agent* agent) const;

			const std::list<Room*>& GetRooms() const;

			void CreateRoomFor(Agent* agent);

			void ShowBedrooms( Agent* murderer ) const;
			void ShowCommonRooms(Agent* agent) const;
			void ShowOwnBedroom(Agent* agent) const;

			void AddAgentProbabilities(Agent* agent);

			float GetProb(Agent* agent, Room* room) const;
			float GetProbOthers(Agent* agent, Room* room) const;
			float GetProbAlone(Agent* agent, Room* room) const;
			float GetProbWillBeFound(Agent* agent, Room* room) const;

			void ClearRooms();
			void UpdateAllRooms() const;

			void ShowEverything(Agent* seer) const;

		private:
			std::map<RoomName, Room*> m_mapRoom;
			std::map<Agent*, Room*> m_mapBedroom;
			std::list<Room*> m_rooms;
			std::map< Agent*, std::map<Room*, float> > m_probabilities;
	};
}

#endif