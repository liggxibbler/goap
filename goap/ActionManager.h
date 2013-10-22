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

		const Action* GetAction(ActionType at);
		Action* GetNewAction(ActionType at);

	private:
		std::map<ActionType, Action*> m_mapAction;
	};
}

#endif