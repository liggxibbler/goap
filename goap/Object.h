#ifndef _GOAP_OBJECT_H_
#define _GOAP_OBJECT_H_

#include "Common.h"
#include <map>
#include <string>

namespace GOAP
{
	class Room;
	class RoomManager;

	namespace Op
	{
		class OperatorManager;
	}

	class Object
	{
	public:
		Object();
		Object(std::string name, Object* owner = NULL);
		Object(const Object& other);
		~Object();

		int GetAttrib(AttributeType at);
		void SetAttribute(AttributeType at, int val);
		int& operator [] (AttributeType at);

		int GetID();
		Object* GetOwner();

		std::string GetName();

		Room* GetRoom();
		void SetRoom(Room* room);

		void SetOwner(Object* owner);

		virtual Object* Clone() = 0;
		//virtual operator ObjectType () = 0;
		virtual bool Update(Op::OperatorManager* om, RoomManager* rm, int turn) = 0;
		virtual int GetCompoundType() = 0;
		virtual void Examine() = 0;

	protected:

		virtual void InitAttribMap();

		static int s_numObjects;
		int m_id;
		std::string m_name;
		std::map<AttributeType, int*> m_attribs;
		int m_posx;
		int m_posy;
		int m_room;

		Object* m_owner;
		Room* m_roomInstance;
	};
}

#endif
