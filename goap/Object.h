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
		
		int GetAttrib(AttributeType at);
		void SetAttrib(AttributeType at, int val);
		virtual operator ObjectType ();// = 0;
		/*const*/ int& operator [] (AttributeType at); 
	protected:
		char* m_id;
		std::map<AttributeType, int*> m_attribs;
		//Position m_position;
		int m_posx;
		int m_posy;
	};
}

#endif