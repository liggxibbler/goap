#include "ActionManager.h"

using namespace GOAP;

ActionManager::ActionManager()
{
	m_mapAction[ACTION_STAB] = new Stab();
	m_mapAction[ACTION_GOTO] = new GoTo();
	m_mapAction[ACTION_TAKE] = new Take();

	InitializePrototypes();
}

ActionManager::ActionManager(const ActionManager& other)
{
}

ActionManager::~ActionManager()
{
}

Action* ActionManager::GetAction(ActionType at)
{
	return m_mapAction[at];
}

Action* ActionManager::GetNewAction(ActionType at)
{
	return m_mapAction[at]->Clone();
}

void ActionManager::InitializePrototypes()
{
	std::map<ActionType, Action*>::iterator prototypes;
	Action* action;
	for(prototypes = m_mapAction.begin(); prototypes != m_mapAction.end(); ++prototypes)
	{
		action = prototypes->second;
		action->Initialize();
	}
}