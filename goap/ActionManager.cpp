#include "ActionManager.h"

using namespace GOAP;

ActionManager::ActionManager()
{
	m_mapAction[ACTION_STAB] = new Stab();
}

ActionManager::ActionManager(const ActionManager& other)
{
}

ActionManager::~ActionManager()
{
}

const Action* ActionManager::GetAction(ActionType at)
{
	return m_mapAction[at];
}

Action* ActionManager::GetNewAction(ActionType at)
{
	return m_mapAction[at]->Clone();
}