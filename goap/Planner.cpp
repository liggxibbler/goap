#include "Planner.h"

using namespace GOAP;

PlanStatus Planner::Plan(Agent* agent, ActionManager* am, Op::OperatorManager* om, Goal* plan)
{
	m_frontier.push_back(agent->GetGoal());
	return PlanWorkHorse(agent, am, om, plan);
}

PlanStatus Planner::PlanWorkHorse(Agent* agent, ActionManager* am, Op::OperatorManager* om, Goal* plan)
{

	/*
	Do this:

	METHOD : PickNextGoal()
	take cheapest goal off short list
	
	*/

	m_currentGoal = PickNextGoal();

	if(m_currentGoal == NULL)
	{
	// this means that the short list is empty
	// which means either that the planner has failed to find a plan
		return PLAN_STAT_FAIL;
	}

	if(m_currentGoal->Evaluate(om))
	{
		/*
		if goal is satisfied:
			DON'T return path from current goal to root of goal tree (successive parent nodes)
			(actually)
			return just the goal node, it will contain a pointer to its parent node.
			since the plan stays the same unless something is really different, the tree can exist until plan becomes obsolete
		*/
		plan = m_currentGoal;
		return PLAN_STAT_SUCCESS;
	}

	

	FillLongList(m_currentGoal, agent, am); /* METHOD : FillLongList(Agent, ActionManager)
												for each condition in that goal:
													for all actions in agent:
														if action may satisfy condition: i.e. has effect that may satisfy condition
															copy condition to action
															add action to long list
											*/

	
											
	ExtendFrontier(agent);					/* METHOD : ExtendFrontier(Agent)
												for all actions in long list:
													if all null semantics can be instantiated using Agent's list:
														in such a way that the list remains sorted by cost + heuristic:
															add all possible instances of action to short list
															add all preconditions of action to a goal node as child of current goal with action on the edge
											*/
	

	ClearLongList(); // clear the long list

	/*
	for all actions in short list:
		do the same thing, until:
			either you reach maximum plan depth
			or you reach a goal that is already satisfied in the current state
			or the frontier is empty and no plan is found
	*/
	
	return PlanWorkHorse(agent, am, om, plan);
}

void Planner::FillLongList(Goal* goal, Agent* agent, ActionManager* am)
{
	/*
	for each condition in that goal:
		for all actions in agent:
			if action may satisfy condition: i.e. has effect that may satisfy condition
				copy condition to action
				add action to long list
	*/

	std::list<Condition>::iterator condsIter;
	std::list<ActionType>::iterator actIter;

	Action* action = NULL;

	for(condsIter = goal->GetFirstCondition(); condsIter != goal->GetLastCondition(); ++condsIter)
	{
		for(actIter = agent->FirstAction(); actIter != agent->LastAction(); ++actIter)
		{
			action = am->GetAction(*actIter);
			if( action->MightSatisfy(*condsIter) )
			{
				action = am->GetNewAction(*actIter); // to keep the prototype untouched
				action->CopyArgsFromCondition(*condsIter);
				m_actionLongList.push_back(action);
			}
		}
	}
}
