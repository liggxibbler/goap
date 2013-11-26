#ifndef _GOAP_ROOM_H_
#define _GOAP_ROOM_H_

#include <string>
#include <list>

namespace GOAP
{
	class Object;
	class Agent;

	class Room
	{
	public:
		Room();
		Room(const Room& other);
		Room(std::string name);
		~Room();

		void SetLeft(Room* left);
		void SetRight(Room* right);
		Room* GetLeft();
		Room* GetRight();

		Object* AddObject(std::string name);
		void AddObject(Object* obj);

		std::string GetName();

		Room* Clone();

		std::list<Object*>::iterator GetFirstObject();
		std::list<Object*>::iterator GetLastObject();

		std::list<Agent*>::iterator GetFirstAgent();
		std::list<Agent*>::iterator GetLastAgent();

	private:
		std::string m_name;
		std::list<Object*> m_objects;
		std::list<Agent*> m_agents;
		
		Room* m_left;
		Room* m_right;
	};
}

#endif