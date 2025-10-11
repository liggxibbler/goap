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

		void Initialize();

		PlanStatus Devise(Agent* agent, Plan* plan) const;

	public:
		Action* GetWander(Agent* agent) const;

		Op::OperatorManager& GetOperatorManager();
		RoomManager& GetRoomManager();
		ActionManager& GetActionManager();

	private:
		Goal* PickNextGoal(std::list<Goal*>& frontier) const;
		void FillLongList(Goal* goal, Agent* agent, const ActionManager& am, std::list<LongListEntry>& longList) const;
		void ExpandFrontier(const RoomManager& roomManager, std::list<Goal*>& frontier, std::list<LongListEntry>& longList, Goal* currentGoal, Agent* agent) const;

	private:
		PlanStatus DeviseWorkHorse(Agent* agent, Plan* goal) const;

		Op::OperatorManager m_operatorManager;
		RoomManager m_roomManager;
		ActionManager m_actionManager;
	};
}

#endif