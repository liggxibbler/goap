#ifndef _GOAP_PLANNER_H_
#define _GOAP_PLANNER_H_

#include "Object.h"
#include "Agent.h"
#include "ActionManager.h"
#include "OperatorManager.h"
#include "Combination.h"
#include "Goal.h"
#include <list>

namespace GOAP
{
	class Planner
	{
	public:
		Planner();
		Planner(const Planner& other);
		~Planner();

		PlanStatus Plan(Agent* agent, ActionManager* am, Op::OperatorManager* om, Goal* plan);
	
	private:
		Goal* PickNextGoal();
		void FillLongList(Goal* goal, Agent* agent, ActionManager* am);
		void ClearLongList();
		void ExtendFrontier(Agent* agent);

	private:

		PlanStatus PlanWorkHorse(Agent* agent, ActionManager* am, Op::OperatorManager* om, Goal* goal); // planner workhorse

		Goal* m_currentGoal;
		std::list<Goal*> m_frontier;			// The portion of the search space that is currently being analyzed
		std::list<Action*> m_actionLongList;	// Initial candidates for previous action to have been taken
	};
}

#endif