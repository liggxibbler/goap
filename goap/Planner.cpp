#include "Planner.h"

using namespace GOAP;

PlanStatus Planner::Plan(Agent* agent, ActionManager* am, std::list<Action*>& plan)
{
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