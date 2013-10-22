#ifndef _GOAP_PLANNER_H_
#define _GOAP_PLANNER_H_

#include "Object.h"
#include "Agent.h"
#include "ActionManager.h"
#include "Condition.h"
#include <list>
#include <stack>


namespace GOAP
{
	class Planner
	{
	public:
		Planner();
		Planner(const Planner& other);
		~Planner();
		Action** Plan(Agent* agent, ActionManager* am);//, OperatorManager* om);
	
	private:
		std::stack<Condition> m_goalStack;
		std::list<Action*> m_actionQueue;
		int m_depth;
	};
}

#endif