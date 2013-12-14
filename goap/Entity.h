#ifndef _GOAP_ENTITY_H_
#define _GOAP_ENTITY_H_

#include "Common.h"
#include <map>
#include <string>

namespace GOAP
{
	class Entity
	{
	public:
		Entity();
		Entity(std::string name, Entity* owner = NULL);
		Entity(const Entity& other);
		~Entity();

		int GetAttrib(AttributeType at);
		void SetAttribute(AttributeType at, int val);
		virtual operator EntityType ();// = 0;
		/*const*/ int& operator [] (AttributeType at);

		int GetID();
		Entity* GetOwner();

		std::string GetName();

	protected:
		static int s_numEntities;
		int m_id;
		std::string m_name;
		std::map<AttributeType, int*> m_attribs;
		//Position m_position;
		int m_posx;
		int m_posy;
		Entity* m_owner;
	};
}

#endif
