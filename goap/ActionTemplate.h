#ifndef _GOAP_ACTIONTEMPLATE_H_
#define _GOAP_ACTIONTEMPLATE_H_

#include "Common.h"
#include "Action.h"
#include "SemanticCondition.h"
#include "Object.h"

namespace GOAP
{
	class ActionTemplate
	{
	public:
		virtual void Action* CreateNew() = 0;
	protected:
		OperandSemanticType* m_semantics;
		SemanticCondition* m_preconds;
		SemanticCondition* m_effects;
	};
}

#endif