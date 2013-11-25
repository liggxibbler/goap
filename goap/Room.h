#ifndef _GOAP_ROOM_H_
#define _GOAP_ROOM_H_

#include <string>
#include <map>

namespace GOAP
{
	class Object;

	class Room
	{
	public:
		Room();
		Room(const Room& other);
		Room(std::string name);
		~Room();

		void SetLeft(Room* left);
		void SetRight(Room* right);
		
		Object* AddObject(std::string name);
		void AddObject(Object* obj);

		std::string GetName();

		Room* Clone();

	private:
		std::string m_name;
		std::map<std::string, Object*> m_objects;
		Room* m_left;
		Room* m_right;
	};
}

#endif