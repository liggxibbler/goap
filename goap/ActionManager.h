#ifndef _GOAP_ACTIONMANGER_H_
#define _GOAP_ACTIONMANGER_H_

#include "ActionTemplate.h"
#include "Action.h"
#include "Common.h"
#include <map>


namespace GOAP
{
	class ActionManager
	{
		ActionManager();
		ActionManager(const ActionManager& other);
		~ActionManager();

		Action* GetAction(ActionType);
		ActionTemplate* GetActionTemplate(ActionType);

	private:
		std::map<ActionType, ActionTemplate*> m_mapTemplate;
		std::map<ActionType, Action*> m_mapAction;
	};
}

#endif