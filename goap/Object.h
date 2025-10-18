#ifndef _GOAP_OBJECT_H_
#define _GOAP_OBJECT_H_

#include <map>
#include <string>

#include "Common.h"

namespace GOAP
{
	class Room;
	class RoomManager;
	class ActionManager;
	class Planner;

	namespace Op
	{
		class OperatorManager;
		class Operator;
	}

	class Object
	{
	public:
		Object();
		Object(std::string name, Object* owner = nullptr);
		Object(const Object& other);
		~Object();

	private:
		int GetAttribute(AttributeType at);
		int& operator [] (AttributeType at);
	public:

		int GetID() const;
		Object* GetOwner();

		std::string GetName() const;

		Room* GetRoom() const;
		void SetRoom(Room* room);

		void SetOwner(Object* owner);

		virtual Object* Clone() const = 0;
		//virtual operator ObjectType () = 0;
		virtual void Update(Planner & planner, int turn) = 0;
		virtual ObjectType GetCompoundType() const = 0;
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
	private:
		friend class Op::Operator;
	};
}

#endif
