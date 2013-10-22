#include "Planner.h"

using namespace GOAP;

Action** Planner::Plan(Agent* agent, ActionManager* am)
{
	// Read agent's goal, push it on goal stack
	m_goalStack.push(agent->Goal());

	// Go through agent's actions
	std::list<ActionType>::iterator actionIter;

	for(actionIter = agent->FirstAction(); actionIter != agent->LastAction(); actionIter++)
	{
		Action* currentAction = (Action*)am->GetAction(*actionIter);
		//if action == m_goalStack.top()
		//	copy condition to action
		//	i.e. act = am->getnew(*actioniter), act.copy(condition);
		//  for semantic in action
		//		if action[semantic] = null then
		//			action[semantic] = unify(action.semantic.type)
		//			if action[semantic] = null then break (i.e. try next actiontype)
		//	
	}
	return NULL;
}