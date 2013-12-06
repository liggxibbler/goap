#ifndef _GOAP_ROOM_H_
#define _GOAP_ROOM_H_

#include <string>
#include <list>
#include <set>
#include "Common.h"
#include "Object.h"

namespace GOAP
{
	class Agent;

	class Room : public Object
	{
	public:
		Room();
		Room(const Room& other);
		Room(std::string name, RoomName rn);
		~Room();

		void SetLeft(Room* left);
		void SetRight(Room* right);
		Room* GetLeft();
		Room* GetRight();

		Object* AddObject(std::string name);
		void AddObject(Object* obj);

		Agent* AddAgent(std::string name);
		void AddAgent(Agent* agent);

		std::string GetName();

		std::list<Object*>::iterator GetFirstObject();
		std::list<Object*>::iterator GetLastObject();

		std::set<Agent*>::iterator GetFirstAgent();
		std::set<Agent*>::iterator GetLastAgent();

		RoomName GetType();

		int GetID();

		virtual bool Update(World* world, int turn);

		void MarkForDeletion(Agent* agent);
		void MarkForAddition(Agent* agent);
		void UpdateAgentPositions();

		virtual Object* Clone();

	private:
		void ClearMarkedAgents();
		void AddMarkedAgents();
		
		static int s_nextID;

		RoomName m_type;
		//std::string m_name;
		std::list<Object*> m_objects;
		std::set<Agent*> m_agents;
		std::set<Agent*> m_markedForDeletion;
		std::set<Agent*> m_markedForAddition;
		int m_ID;

		Room* m_left;
		Room* m_right;
	};
}

#endif