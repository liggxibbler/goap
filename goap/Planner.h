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

		PlanStatus Devise(Agent* agent, const ActionManager& am, const Op::OperatorManager& om, const RoomManager& roomManager, Plan* plan);

		void ClearPlanTree();

	private:
		Goal* PickNextGoal();
		void FillLongList(Goal* goal, Agent* agent, const ActionManager& am);
		void ClearLongLists();
		void ExpandFrontier(const RoomManager& roomManager, Agent* agent);

	private:
		PlanStatus DeviseWorkHorse(Agent* agent, const ActionManager& am, const Op::OperatorManager& om, const RoomManager& roomManager, Plan* goal); // planner workhorse

		Goal* m_currentGoal;
		std::list<Goal*> m_frontier;				// The portion of the search space that is currently being analyzed
		std::list<std::pair<Action*, Condition>> m_actionLongList;		// Initial candidates for previous action to have been taken
		std::list< Condition > m_condRemoveList;	// The conditions that the action candidates might satisfy
		//std::map< Action*, std::list<Condition> > m_longList;
		std::list<Goal*> m_actInstPreconds;
	};
}

#endif