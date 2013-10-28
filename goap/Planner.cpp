#include "Planner.h"

using namespace GOAP;

PlanStatus Planner::Plan(Agent* agent, ActionManager* am, Op::OperatorManager* om, Goal* plan)
{
	m_frontier.push_back(agent->GetGoal());
	return PlanWorkHorse(agent, am, om, plan);
}

PlanStatus Planner::PlanWorkHorse(Agent* agent, ActionManager* am, Op::OperatorManager* om, Goal* plan)
{
	for(m_currentGoal = PickNextGoal(); m_currentGoal != NULL; )
	{
		if(m_currentGoal->Evaluate(om))
		{
			/*
			if goal is satisfied:
			return just the goal node, it will contain a pointer to its parent node.
			since the plan stays the same unless something is really different, the tree can exist until plan becomes obsolete
			*/
			plan = m_currentGoal;
			return PLAN_STAT_SUCCESS;
		}

		FillLongList(m_currentGoal, agent, am); // find all action candidates
		ExtendFrontier(agent);					// finalize possible actions
		ClearLongList();						// clear candidate list
	}
	
	// this means that the short list is empty
	// which means that the planner has failed to find a plan
	plan = NULL;
	return PLAN_STAT_FAIL;
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


void Planner::ClearLongList()
{
	std::list<Action*>::iterator iter;
	for(iter = m_actionLongList.begin(); iter != m_actionLongList.end(); ++iter)
	{
		// Delete every action prototype on the long list
		delete *iter;
		m_actionLongList.remove(*iter);
	}
}

void Planner::ExtendFrontier(Agent* agent)
{
	/* METHOD : ExtendFrontier(Agent)
	for all actions in long list:
		if all null semantics can be instantiated using Agent's list:
			in such a way that the list remains sorted by cost + heuristic:
				add all possible instances of action to short list
				add all preconditions of action to a goal node as child of current goal with action on the edge
	*/
	
	std::list<Action*>::iterator iter;
	Action* act;
	std::vector<Action*> vecAct;
	
	std::list<Action*> instances;
	
	std::list<Action*>::iterator instIter = instances.begin();

	for(iter = m_actionLongList.begin(); iter != m_actionLongList.end(); ++iter)
	{
		act = *iter;
		if(!act->GetPossibleInstances(agent, instances))
		{
			return;
		}
	}

	//	for each action instance:
	//		conds = which conditions of the current goal it might satisfy
	//		nextGoal = goal - conds + action.preconds
	//		add nextGoal to GoalsMadeFromInstances
	// m_frontier.splice(m_frontier.end(), GoalsMadeFromPreCondsOfInstances);
}

Goal* Planner::PickNextGoal()
{
	return NULL;
}