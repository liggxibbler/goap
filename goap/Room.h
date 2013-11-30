#ifndef _GOAP_ROOM_H_
#define _GOAP_ROOM_H_

#include <string>
#include <list>
#include "Common.h"

namespace GOAP
{
	class Object;
	class Agent;

	class Room
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

		Room* Clone();

		std::list<Object*>::iterator GetFirstObject();
		std::list<Object*>::iterator GetLastObject();

		std::list<Agent*>::iterator GetFirstAgent();
		std::list<Agent*>::iterator GetLastAgent();

		RoomName GetType();

		int GetID();

	private:
		static int s_nextID;

		RoomName m_type;
		std::string m_name;
		std::list<Object*> m_objects;
		std::list<Agent*> m_agents;
		int m_ID;

		Room* m_left;
		Room* m_right;
	};
}

#endif