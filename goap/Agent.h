#ifndef _GOAP_AGENT_H_
#define _GOAP_AGENT_H_

//#include "ActionTemplate.h"
#include "Common.h"
#include "Object.h"
#include "Condition.h"
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

		std::list<ActionType>::iterator FirstAction();
		std::list<ActionType>::iterator LastAction();

		virtual operator ObjectType ();
		Condition& Goal();

	protected:
		Condition m_goal;
		std::list<ActionType> m_actions;
		int m_height;
		int m_weight;
		int m_isAlive;
	};
}

#endif