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
	private:
		ActionManager();
		ActionManager(const ActionManager& other);
		~ActionManager();
	
	public:
		
		static ActionManager* Instance();

		Action* GetAction(ActionType at);
		int GetSuspicion(ActionType);

		Action* GetNewAction(ActionType at);
		void InitializePrototypes();
		

	private:
		std::map<ActionType, Action*> m_mapAction;
		std::map<ActionType, int> m_mapSuspect;
	};
}

#endif