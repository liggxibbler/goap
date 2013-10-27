#ifndef _GOAP_PLANNER_H_
#define _GOAP_PLANNER_H_

#include "Object.h"
#include "Agent.h"
#include "ActionManager.h"
#include "Goal.h"
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

		Goal* PickNextGoal();


		PlanStatus Plan(Agent* agent, ActionManager* am, std::list<Action*>& plan);//, OperatorManager* om);
	
	private:
		std::list<Goal*> m_frontier;			// The portion of the search space that is currently being analyzed
		std::list<Action*> m_actionLongList;	// Initial candidates for previous action to have been taken
	};
}

#endif