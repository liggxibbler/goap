#include "ActionManager.h"

using namespace GOAP;

ActionManager::ActionManager()
{
	m_mapAction[ACTION_STAB]		= new Stab();
	m_mapAction[ACTION_GOTO]		= new GoTo();
	m_mapAction[ACTION_TAKE]		= new Take();
	m_mapAction[ACTION_BLUDGEON]	= new Bludgeon();
	m_mapAction[ACTION_STRANGLE]	= new Strangle();
	m_mapAction[ACTION_SHOOT]		= new Shoot();
	m_mapAction[ACTION_WAITFOR]		= new WaitFor();
    m_mapAction[ACTION_DROP]        = new Drop();

	m_mapSuspect[ACTION_STAB]		= 2;
	m_mapSuspect[ACTION_GOTO]		= 1000;
	m_mapSuspect[ACTION_TAKE]		= 1;
	m_mapSuspect[ACTION_BLUDGEON]	= 2;
	m_mapSuspect[ACTION_STRANGLE]	= 2;
	m_mapSuspect[ACTION_SHOOT]		= 2;
	m_mapSuspect[ACTION_WAITFOR]	= 1000;
    m_mapSuspect[ACTION_DROP]       = 1;

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

ActionManager* ActionManager::Instance()
{
	static ActionManager am;
	return &am;
}

int ActionManager::GetSuspicion(ActionType at)
{
	return m_mapSuspect[at];
}