#ifndef _GOAP_OBJECT_H_
#define _GOAP_OBJECT_H_

#include <map>
#include "Common.h"

namespace GOAP
{
	class Object
	{
	public:
		Object();
		Object(const Object& other);
		~Object();
	
		/*Object()
		{
			m_attribs[POSX] = &m_posx;
			m_attribs[POSY] = &m_posy;
		}*/
		int GetAttrib(AttributeType at);/*
		{
			return *m_attribs[at];
		}*/
		void SetAttrib(AttributeType at, int val);/*
		{
			*m_attribs[at] = val;
		}*/
	protected:
		std::map<AttributeType, int*> m_attribs;
		Position m_position;
	};
}

#endif