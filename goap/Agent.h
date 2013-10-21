#ifndef _GOAP_AGENT_H_
#define _GOAP_AGENT_H_

//#include "ActionTemplate.h"
#include "Object.h"
#include <list>

namespace GOAP
{
	class Agent : public Object
	{
	public:
		Agent();
		Agent(char* name);
		Agent(const Agent& other);
		~Agent();

		virtual operator ObjectType ();

	protected:
		std::list<ActionType> m_actions;
		int m_height;
		int m_weight;
		int m_isAlive;
	};
}

#endif