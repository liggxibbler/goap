#ifndef _GOAP_OBJECTMANAGER_H_
#define _GOAP_OBJECTMANAGER_H_

#include <map>

namespace GOAP
{
	class Object;

	class ObjectManager
	{
		Object* GetObject(int name);
	private:
		std::map<int, Object*> m_objects;
	};
}

#endif