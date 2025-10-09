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
	struct LongListEntry
	{
		Action* action;
		Condition condition;
	};

	class Planner
	{
	public:
		Planner();
		Planner(const Planner& other);
		~Planner();

		PlanStatus Devise(Agent* agent, const ActionManager& am, const Op::OperatorManager& om, const RoomManager& roomManager, Plan* plan);

	private:
		Goal* PickNextGoal(std::list<Goal*>& frontier);
		void FillLongList(Goal* goal, Agent* agent, const ActionManager& am, std::list<LongListEntry>& longList);
		void ExpandFrontier(const RoomManager& roomManager, std::list<Goal*>& frontier, std::list<LongListEntry>& longList, Goal* currentGoal, Agent* agent);

	private:
		PlanStatus DeviseWorkHorse(Agent* agent, const ActionManager& am, const Op::OperatorManager& om, const RoomManager& roomManager, Plan* goal);
	};
}

#endif