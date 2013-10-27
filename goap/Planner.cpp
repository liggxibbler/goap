#include "Planner.h"

using namespace GOAP;

PlanStatus Planner::Plan(Agent* agent, ActionManager* am, std::list<Action*>& plan)
{
	/*
	Do this:

	METHOD : PickNextGoal()
	take least costly goal off short list

	if goal is satisfied:
		DON'T return path from current goal to root of goal tree (successive parent nodes)
		(actually)
		return just the goal node, it will contain a pointer to its parent node.
		since the plan stays the same unless something is really different, the tree can exist until plan becomes obsolete

	METHOD : FillLongList(Agent, ActionManager)
	for each condition in that goal:
		for all actions in agent:
			if action may satisfy condition: i.e. has effect that may satisfy condition
				copy condition to action
				add action to long list
	
	METHOD : FindPreviousGoals(Agent)
	for all actions in long list:
		if all null semantics can be instantiated using Agent's list:
			add all possible instances of action to short list
			add all preconditions of action to a goal node as child of current goal with action on the edge
	
	clear the long list
	
	sort the short list by cost + heuristic
	
	for all actions in short list:
		do the same thing, until:
			either you reach maximum plan depth
			or you reach a goal that is already satisfied in the current state
	*/


	// Read agent's goal, push it on goal stack
	m_goalStack.push(agent->Goal());

	// Go through agent's actions
	std::list<ActionType>::iterator actionIter;

	for(actionIter = agent->FirstAction(); actionIter != agent->LastAction(); actionIter++)
	{
		Action* currentAction = (Action*)am->GetAction(*actionIter);
		//if action == m_goalStack.top()
		if( currentAction->MightSatisfy(m_goalStack.top()) != currentAction->GetLastEffect() )
		{
			//	copy condition to action
			//	i.e. act = am->getnew(*actioniter), act.copy(condition);
			currentAction->CopyArgsFromCondition(m_goalStack.top());
			
			//  for semantic in action
			std::list<ConditionParameter>::iterator argIter;
			for(argIter = currentAction->GetFirstArg(); argIter != currentAction->GetLastArg(); ++argIter)
			{
				//		if action[semantic] = null then
				if ((*argIter).instance = NULL)
				{
					std::list<Object*>::iterator currentMatch = agent->FirstObject();
					//	action[semantic] = unify(action.semantic.type)
					std::list<Object*>::iterator objIter = agent->Unify((*argIter).type, currentMatch);
					//currentAction->GetArgBySemantic(OP_SEMANTIC_TYPE_DESTINATION)->instance
					//	if action[semantic] = null then break (i.e. try next actiontype)					
				}
				if(objIter == agent->LastObject())
				{
					break;
				}
			}
		}
	}
	return PLAN_STAT_SUCCESS;
}