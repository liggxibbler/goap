#ifndef _GOAP_PLANNER_H_
#define _GOAP_PLANNER_H_

#include "Object.h"
#include "Agent.h"
#include "ActionManager.h"
#include "OperatorManager.h"
#include "RoomManager.h"
#include "OrderedPair.h"
#include "Goal.h"
#include "Plan.h"

#include <list>
#include <map>

#define MAX_PLAN_DEPTH 5

namespace GOAP
{
	class Planner
	{
	public:
		Planner();
		Planner(const Planner& other);
		~Planner();

		PlanStatus Devise(Agent* agent, ActionManager* am, Op::OperatorManager* om, Plan* plan);

		class CompareGoals
		{
		public:
			bool operator ()(Goal* g1, Goal* g2)
			{
				// keep the nullptr pointer at the beginning
				if(g1 == 0)
				{
					return true;
				}
				else if (g2 == 0)
				{
					return false;
				}
				// and sort the rest in descending order,
				// so the least costly action is always at the end
				else
				{
					return (g1->GetCost()) > (g2->GetCost());
				}
			}
		} myCompare;

		void ClearPlanTree();

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