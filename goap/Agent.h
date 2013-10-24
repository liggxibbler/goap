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

		std::list<Object*>::iterator FirstObject();
		std::list<Object*>::iterator LastObject();

		virtual operator ObjectType ();
		Condition& Goal();

		//std::list<Object*>::iterator Unify(ObjectType ot, std::list<Object*>::iterator from);

	protected:
		Condition m_goal;
		std::list<ActionType> m_actions;
		std::list<Object*> m_objects;
		int m_height;
		int m_weight;
		int m_isAlive;
	};
}

#endif