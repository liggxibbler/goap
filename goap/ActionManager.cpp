#include "ActionManager.h"

using namespace GOAP;

ActionManager::ActionManager()
{
	m_mapAction[ActionType::STAB]		= new Stab();
	m_mapAction[ActionType::GOTO]		= new GoTo();
	m_mapAction[ActionType::TAKE]		= new Take();
	m_mapAction[ActionType::BLUDGEON]	= new Bludgeon();
	m_mapAction[ActionType::STRANGLE]	= new Strangle();
	m_mapAction[ActionType::SHOOT]		= new Shoot();
	m_mapAction[ActionType::WAITFOR]	= new WaitFor();
    m_mapAction[ActionType::DROP]		= new Drop();

	m_mapSuspect[ActionType::STAB]		= true;
	m_mapSuspect[ActionType::GOTO]		= false;
	m_mapSuspect[ActionType::TAKE]		= true;
	m_mapSuspect[ActionType::BLUDGEON]	= true;
	m_mapSuspect[ActionType::STRANGLE]	= true;
	m_mapSuspect[ActionType::SHOOT]		= true;
	m_mapSuspect[ActionType::WAITFOR]	= false;
    m_mapSuspect[ActionType::DROP]		= true;

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

bool ActionManager::GetSuspicion(ActionType at)
{
	return m_mapSuspect[at];
}