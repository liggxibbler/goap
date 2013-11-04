#include "Planner.h"

using namespace GOAP;

Planner::Planner()
{
	m_currentGoal = NULL;
}

PlanStatus Planner::Plan(Agent* agent, ActionManager* am, Op::OperatorManager* om, Goal* plan)
{
	m_frontier.push_back(NULL);
	m_frontier.push_back(agent->GetGoal());
	return PlanWorkHorse(agent, am, om, plan);
}

PlanStatus Planner::PlanWorkHorse(Agent* agent, ActionManager* am, Op::OperatorManager* om, Goal* plan)
{
	for(m_currentGoal = PickNextGoal(); m_currentGoal != NULL; )
	{
		DUMP("Address of current goal is " << m_currentGoal )
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

	CondIter condsIter;
	std::list<ActionType>::iterator actIter;

	Action* action = NULL;
	
	for(condsIter = goal->GetFirstCondition(); condsIter != goal->GetLastCondition(); ++condsIter)
	{
		// XIBB this is risky, if duplicates are possible, they will happen
		// XIBB it would be better if the action long list is a map.first,
		// XIBB and the condition long list is a map.second list of conditions

		for(actIter = agent->FirstAction(); actIter != agent->LastAction(); ++actIter)
		{
			action = am->GetAction(*actIter);
			if( action->MightSatisfy(*condsIter) )
			{
				DUMP("Found action candidate of type " << (ActionType)(*action))
				action = am->GetNewAction(*actIter); // to keep the prototype untouched
				action->CopyArgsFromCondition(*condsIter);
				m_actionLongList.push_back(action);
				m_condLongList.push_back(*condsIter);	// remember which condition the action might satisfy
			}
		}
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
	std::list<Condition>::iterator condIter = m_condLongList.begin();
	Condition cond;

	m_actInstPreconds.clear();	// clear list of goals from last iteration
	m_condRemoveList.clear();

	for(iter = m_actionLongList.begin(); iter != m_actionLongList.end(); ++iter)
	{
		act = *iter;
		cond = *condIter;
		int numInst = act->GetPossibleInstances(agent, instances); 
		if(numInst == 0)
		{
			// this action cannot be used in the plan at this point
			// and will not affect the frontier
			DUMP("Action cannot be instantiated")
			continue;
		}
		else
		{
			for(int i=0; i< numInst; i++)
			{
				m_condRemoveList.push_back(cond);
			}
		}
		++condIter;
	}

	std::list<Action*>::iterator actInstIter;
	condIter = m_condRemoveList.begin();
	Action* action;

	for(actInstIter = instances.begin(); actInstIter != instances.end(); ++actInstIter)
	{
		//		conds = which conditions of the current goal it might satisfy
		action = *actInstIter;
		cond = *condIter;
		Goal* nextGoal = m_currentGoal->Clone();

		nextGoal->RemoveCondition(cond);
		std::list<Condition>::iterator effect;
		
		for(effect = action->GetFirstEffect(); effect != action->GetLastEffect(); ++effect)
		{
			nextGoal->AddCondition(*effect);
		}
		
		nextGoal->SetAction(action);
		nextGoal->SetParent(m_currentGoal);
		m_currentGoal->AddChild(nextGoal);

		m_frontier.push_back(nextGoal);
		++condIter;
	}
	
}

Goal* Planner::PickNextGoal()
{
	Goal* next = m_frontier.back();
	m_frontier.remove(next);
	return next;
}

void Planner::ClearLongList()
{
	std::list<Action*>::iterator iter;
//	Action* act;
	for(iter = m_actionLongList.begin(); iter != m_actionLongList.end(); iter = m_actionLongList.begin())
	{
		// Delete every action prototype on the long list
		m_actionLongList.remove(*iter);
	}
	m_actionLongList.clear();
	
	//DUMP("CLEARING LONG LIST")
}