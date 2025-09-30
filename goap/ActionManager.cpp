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

const Action* ActionManager::GetActionPrototype(ActionType at) const
{
	return m_mapAction.at(at);
}

Action* ActionManager::GetNewAction(ActionType at) const
{
	return m_mapAction.at(at)->Clone();
}

void ActionManager::InitializePrototypes()
{
	for (auto& pair : m_mapAction)
	{
		pair.second->Initialize();
	}
}

bool ActionManager::GetSuspicion(ActionType at) const
{
	return m_mapSuspect.at(at);
}