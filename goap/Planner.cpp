#include "Planner.h"

using namespace GOAP;

Planner::Planner()
{
	m_currentGoal = NULL;
}

PlanStatus Planner::Devise(Agent* agent, ActionManager* am, Op::OperatorManager* om, Plan* plan)
{
	ClearPlanTree();
	m_frontier.push_back(NULL);
	m_frontier.push_back(agent->GetGoal());
	return DeviseWorkHorse(agent, am, om, plan);
}

PlanStatus Planner::DeviseWorkHorse(Agent* agent, ActionManager* am, Op::OperatorManager* om, Plan* plan)
{
	for(m_currentGoal = PickNextGoal(); m_currentGoal != NULL; m_currentGoal = PickNextGoal() )
	{
		if(m_currentGoal == NULL)
		// Searched entire action space up to max depth
		{
			break;
		}

		DUMP_NL( "Trying level " << m_currentGoal->GetDepth() << " goal at " <<
			m_currentGoal << " with " << m_currentGoal->GetNumConditions() << " conditions...\n")
		
		if(m_currentGoal->GetDepth() > MAX_PLAN_DEPTH)
		{
			// Don't process goals that need more than MAX_PLAN_DPETH actions
			continue;
		}

		if(m_currentGoal->Evaluate(om))
		{
			/*
			if goal is satisfied:
			return just the goal node, it will contain a pointer to its parent node.
			since the plan stays the same unless something is really different, the tree can exist until plan becomes obsolete
			*/
			plan->SetPlan(m_currentGoal);
			if(plan->Validate())
			{
				DUMP("VALID PLAN FOUND")
				plan->SetStatus(PLAN_STAT_SUCCESS);
				return PLAN_STAT_SUCCESS;
			}
			else
			{
				plan->SetPlan(0);
				DUMP("PLAN NOT VALID")
			}
		}
		DUMP( "===Expanding frontier")
		FillLongList(m_currentGoal, agent, am); // find all action candidates
		ExpandFrontier(agent);					// finalize possible actions
		ClearLongLists();						// clear candidate list
	}
	
	// this means that the short list is empty
	// which means that the planner has failed to find a plan
	plan->SetStatus(PLAN_STAT_FAIL);
	return PLAN_STAT_FAIL;
}

void Planner::FillLongList(Goal* goal, Agent* agent, ActionManager* am)
{
	/*
	for all actions in agent:
		for each condition in that goal:
			if action may satisfy condition: i.e. has effect that may satisfy condition
				copy condition to action
				add action to long list
	*/

	CondIter condsIter;
	std::list<ActionType>::iterator actIter;

	Action* action = NULL;
	
	for(actIter = agent->FirstAction(); actIter != agent->LastAction(); ++actIter)
	{
		for(condsIter = goal->GetFirstCondition(); condsIter != goal->GetLastCondition(); ++condsIter)
		{
			// XIBB this is risky, if duplicates are possible, they will happen
			// XIBB it would be better if the action long list contains keys mapped to
			// XIBB the condition long list as a list of conditions


			action = am->GetAction(*actIter); // get action prototype
			if( action->MightSatisfy(*condsIter) )
			{
				DUMP("Found level " << m_currentGoal->GetDepth() << " action of type " << (std::string)(*action))
				action = am->GetNewAction(*actIter); // to keep the prototype untouched
				if (action->CopyArgsFromCondition(*condsIter) == true)
				{
					action->UpdateConditionInstances();
					m_actionLongList.push_back(action);
					m_condLongList.push_back(*condsIter);	// remember which condition the action might satisfy
				}
				else
				{
					std::cout << "Something's not right" << (std::string)(*action) << std::endl;
					std::cin.get();
				}				
			}
		}
	}
}

void Planner::ExpandFrontier(Agent* agent)
{
	/* METHOD : ExpandFrontier(Agent)
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
			DUMP("Action " << (std::string)(*act) << " cannot be instantiated")
			continue;
		}
		else
		{
			act->Debug();
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
		action->UpdateConditionInstances();		
		cond = *condIter;
		Goal* nextGoal = m_currentGoal->Clone();

		nextGoal->RemoveCondition(cond);
		std::list<Condition>::iterator precond;
		Goal* preconds = action->GetPreconds();

		for(precond = preconds->GetFirstCondition(); precond != preconds->GetLastCondition(); ++precond)
		{
			nextGoal->AddCondition(*precond);
		}

		nextGoal->SetAction(action);
		nextGoal->SetParent(m_currentGoal);
		nextGoal->SetCost(m_currentGoal->GetCost() + nextGoal->GetAction()->Cost(RoomManager::Instance()));
		nextGoal->SetDepth(m_currentGoal->GetDepth() + 1);
		m_currentGoal->AddChild(nextGoal);

		m_frontier.push_back(nextGoal);
		++condIter;
	}

	if(m_frontier.size() > 1)
	{
		// sort frontier by cost of actions
		m_frontier.sort(myCompare);
	}
	
}

Goal* Planner::PickNextGoal()
{
	Goal* next = m_frontier.back();
	m_frontier.remove(next);
	return next;
}

void Planner::ClearLongLists()
{
	std::list<Action*>::iterator iter;
//	Action* act;
	for(iter = m_actionLongList.begin(); iter != m_actionLongList.end(); iter = m_actionLongList.begin())
	{
		// Delete every action prototype on the long list
		m_actionLongList.remove(*iter);
	}
	m_actionLongList.clear();
	
	CondIter condIter;
	condIter = m_condLongList.begin();
	while(condIter != m_condLongList.end())
	{
		// Delete every action prototype on the long list
		m_condLongList.erase(condIter++);
	}

	//DUMP("CLEARING LONG LIST")
}

void Planner::ClearPlanTree()
{
	auto goal(m_frontier.begin());
	while(goal != m_frontier.end())
	{
		if(*goal != 0)
		{
			delete *goal;
		}
		m_frontier.erase(goal++);
	}
}