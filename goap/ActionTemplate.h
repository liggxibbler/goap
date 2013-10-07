#ifndef _GOAP_ACTIONTEMPLATE_H_
#define _GOAP_ACTIONTEMPLATE_H_

#include "Common.h"
#include "Action.h"

namespace GOAP
{
	class ActionTemplate
	{
	public:
		virtual void Action* CreateNew() = 0;
	protected:
		static ObjectType* m_paramTypes;
	};
}

#endif