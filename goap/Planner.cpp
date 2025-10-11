#include "Planner.h"

using namespace GOAP;

GOAP::Planner::Planner()
{	
}

GOAP::Planner::~Planner()
{
}

void Planner::Initialize()
{
	m_roomManager.Initialize();
}

PlanStatus GOAP::Planner::Devise(Agent* agent, Plan* plan) const
{
	return DeviseWorkHorse(agent, plan);
}

Action* GOAP::Planner::GetWander(Agent* agent) const
{
	Room* room = m_roomManager.GetRandomRoom(agent);
	GoTo* gt = new GoTo(room, agent);
	gt->Initialize();
	return gt;
}

Op::OperatorManager& GOAP::Planner::GetOperatorManager()
{
	return m_operatorManager;
}

RoomManager& GOAP::Planner::GetRoomManager()
{
	return m_roomManager;
}

ActionManager& GOAP::Planner::GetActionManager()
{
	return m_actionManager;
}

PlanStatus Planner::DeviseWorkHorse(Agent* agent, Plan* plan) const
{
	std::list<Goal*> frontier;
	frontier.push_back(nullptr);
	frontier.push_back(agent->GetGoal());

	for(Goal* currentGoal = PickNextGoal(frontier); currentGoal != nullptr; currentGoal = PickNextGoal(frontier) )
	{
		if(currentGoal == nullptr)
		// Searched entire action space up to max depth
		{
			break;
		}

		DUMP_NL( "Trying level " << currentGoal->GetDepth() << " goal at " <<
			currentGoal << " with " << currentGoal->GetNumConditions() << " conditions...\n")
		
		if(currentGoal->GetDepth() > MAX_PLAN_DEPTH)
		{
			// Don't process goals that need more than MAX_PLAN_DPETH actions
			continue;
		}

		if(currentGoal->Evaluate(m_operatorManager))
		{
			/*
			if goal is satisfied:
			return just the goal node, it will contain a pointer to its parent node.
			since the plan stays the same unless something is really different, the tree can exist until plan becomes obsolete
			*/
			plan->SetPlan(currentGoal);
			if(plan->Validate(m_operatorManager))
			{
				DUMP("VALID PLAN FOUND")
				plan->SetStatus(PlanStatus::SUCCESS);
				return PlanStatus::SUCCESS;
			}
			else
			{
				plan->SetPlan(nullptr);
				DUMP("PLAN NOT VALID")
			}
		}
		DUMP("===Expanding frontier")
		std::list<LongListEntry> longList;
		FillLongList(currentGoal, agent, m_actionManager, longList); // find all action candidates
		ExpandFrontier(m_roomManager, frontier, longList, currentGoal, agent);					// finalize possible actions
		// TODO: What happens to action candidate pointers on the longList when the list goes out of scope?
	}
	
	// this means that the short list is empty
	// which means that the planner has failed to find a plan
	plan->SetStatus(PlanStatus::FAIL);
	return PlanStatus::FAIL;
}

void Planner::FillLongList(Goal* goal, Agent* agent, const ActionManager& am, std::list<LongListEntry>& longList) const
{
	/*
	for all actions in agent:
		for each condition in that goal:
			if action may satisfy condition: i.e. has effect that may satisfy condition
				copy condition to action
				add action to long list
	*/

	for(const ActionType actionType : agent->GetActions())
	{
		for (const Condition& condition : goal->GetConditions())
		{
			// XIBB this is risky, if duplicates are possible, they will happen
			// XIBB it would be better if the action long list contains keys mapped to
			// XIBB the condition long list as a list of conditions


			const Action* actionPrototype = am.GetActionPrototype(actionType);
			std::optional<const Condition*> compatibleEffect = actionPrototype->GetCompatibleEffect(&condition);
			if(compatibleEffect.has_value())
			{
				condition.CopySemantics(*compatibleEffect.value());
				DUMP("Found level " << m_currentGoal->GetDepth() << " action of type " << actionPrototype->GetName())
				GETKEY
				Action* actionCandidate = am.GetNewAction(actionType); // to keep the prototype untouched
				
				if (actionCandidate->CopyArgInstancesFromCondition(condition))
				{
					actionCandidate->UpdateConditionInstances();
					longList.push_back({ actionCandidate, condition });					
				}
				else
				{
					std::cout << "Something's not right " << actionCandidate->GetName() << std::endl;
					std::cin.get();
				}
			}
		}

		goal->CleanSemanticInstances();
	}
}

void Planner::ExpandFrontier(const RoomManager& roomManager, std::list<Goal*>& frontier, std::list<LongListEntry>& longList, Goal* currentGoal, Agent* agent) const
{
	/* METHOD : ExpandFrontier(Agent)
	for all actions in long list:
		if all null semantics can be instantiated using Agent's list:
			in such a way that the list remains sorted by cost + heuristic:
				add all possible instances of action to short list
				add all preconditions of action to a goal node as child of current goal with action on the edge
	*/
	
	std::list<Action*> instances;
	
	std::list< Condition > condRemoveList;

	for(const LongListEntry& actCondPair : longList)
	{
		int numInst = actCondPair.action->GetPossibleInstances(agent, instances);
		if(numInst == 0)
		{
			// this action cannot be used in the plan at this point
			// and will not affect the frontier
			DUMP("Action " << actCondPair.first->GetName() << " cannot be instantiated")
			continue;
		}
		else
		{
			actCondPair.action->Debug();
			for(int i=0; i< numInst; i++)
			{
				condRemoveList.push_back(actCondPair.condition);
			}
		}		
	}

	std::list<Condition>::iterator condRemoveIter = condRemoveList.begin();

	for(Action* action : instances)
	{
		//		conds = which conditions of the current goal it might satisfy
		action->UpdateConditionInstances();		
		Goal* nextGoal = currentGoal->Clone();

		nextGoal->RemoveCondition(*condRemoveIter);
		std::list<Condition>::iterator precond;
		Goal* preconds = action->GetPreconds();

		for(const Condition& precond : preconds->GetConditionsConst())
		{
			nextGoal->AddCondition(precond);
		}

		nextGoal->SetAction(action);
		nextGoal->SetParent(currentGoal);
		nextGoal->SetCost(currentGoal->GetCost() + action->Cost(roomManager));
		nextGoal->SetDepth(currentGoal->GetDepth() + 1);
		currentGoal->AddChild(nextGoal);

		frontier.push_back(nextGoal);
		++condRemoveIter;
	}

	if(frontier.size() > 1)
	{
		frontier.sort([](const Goal* g1, const Goal* g2)
		{
			// keep the nullptr pointer at the beginning
			if (g1 == nullptr)
				return true;

			if (g2 == nullptr)
				return false;

			// and sort the rest in descending order,
			// so the least costly action is always at the end

			return g1->GetCost() > g2->GetCost();

		});
	}
	
}

Goal* Planner::PickNextGoal(std::list<Goal*>& frontier) const
{
	Goal* next = frontier.back();
	frontier.remove(next);
	return next;
}