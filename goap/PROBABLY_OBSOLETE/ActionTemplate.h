#ifndef _GOAP_ACTIONTEMPLATE_H_
#define _GOAP_ACTIONTEMPLATE_H_

#include "Common.h"
#include "Action.h"
#include "Object.h"
#include "AbstractCondition.h"
#include <list>

namespace GOAP
{
	class ActionTemplate
	{
	public:

	protected:
		OperandSemanticType* m_semantics;
		std::list<AbstractCondition> m_preconds;
		std::list<AbstractCondition> m_effects;
	};
}

#endif