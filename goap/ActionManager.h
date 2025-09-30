#ifndef _GOAP_ACTIONMANGER_H_
#define _GOAP_ACTIONMANGER_H_

#include "Action.h"
#include "ActionList.h"
#include "Common.h"
#include <map>


namespace GOAP
{
	class ActionManager
	{
	public:
		ActionManager();
		ActionManager(const ActionManager& other);
		~ActionManager();	
		
		const Action* GetActionPrototype(ActionType at) const;
		bool GetSuspicion(ActionType) const;

		Action* GetNewAction(ActionType at) const;
		void InitializePrototypes();
		

	private:
		std::map<ActionType, Action*> m_mapAction;
		std::map<ActionType, bool> m_mapSuspect;
	};
}

#endif