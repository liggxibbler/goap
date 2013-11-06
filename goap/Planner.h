#ifndef _GOAP_PLANNER_H_
#define _GOAP_PLANNER_H_

#include "Object.h"
#include "Agent.h"
#include "ActionManager.h"
#include "OperatorManager.h"
#include "OrderedPair.h"
#include "Goal.h"
#include "Plan.h"

#include <list>
#include <map>

namespace GOAP
{
	class Planner
	{
	public:
		Planner();
		Planner(const Planner& other);
		~Planner();

		PlanStatus Devise(Agent* agent, ActionManager* am, Op::OperatorManager* om, Plan* plan);

	private:
		Goal* PickNextGoal();
		void FillLongList(Goal* goal, Agent* agent, ActionManager* am);
		void ClearLongLists();
		void ExpandFrontier(Agent* agent);

	private:

		PlanStatus DeviseWorkHorse(Agent* agent, ActionManager* am, Op::OperatorManager* om, Plan* goal); // planner workhorse

		Goal* m_currentGoal;
		std::list<Goal*> m_frontier;				// The portion of the search space that is currently being analyzed
		std::list<Action*> m_actionLongList;		// Initial candidates for previous action to have been taken
		std::list< Condition > m_condLongList;		// The conditions that the action candidates might satisfy
		std::list< Condition > m_condRemoveList;	// The conditions that the action candidates might satisfy
		//std::map< Action*, std::list<Condition> > m_longList;
		std::list<Goal*> m_actInstPreconds;
	};
}

#endif