#ifndef _GOAP_OBJECT_H_
#define _GOAP_OBJECT_H_

#include "Common.h"
#include <map>
#include <string>

namespace GOAP
{
	class Room;

	class Object
	{
	public:
		Object();
		Object(std::string name, Object* owner = NULL);
		Object(const Object& other);
		~Object();
		
		int GetAttrib(AttributeType at);
		void SetAttrib(AttributeType at, int val);
		virtual operator ObjectType ();// = 0;
		/*const*/ int& operator [] (AttributeType at);

		int GetID();
		Object* GetOwner();

		virtual void Update();

		virtual int GetCompoundType();

		std::string GetName();

		//void OnMessage(Telegram& msg);

		virtual void Examine();

		void MayBeFoundIn(int);

		virtual bool CanBeMurderWeapon();

		Room* GetRoom();
		void SetRoom(Room* room);

	protected:
		static int s_numObjects;
		int m_id;
		std::string m_name;
		std::map<AttributeType, int*> m_attribs;
		//Position m_position;
		int m_posx;
		int m_posy;
		int m_room;
		Object* m_owner;
		int m_canBeFoundIn;
		Room* m_roomInstance;
	};
}

#endif