#ifndef _GOAP_ACTION_H_
#define _GOAP_ACTION_H_

#include "Common.h"
#include "Object.h"
#include "Condition.h"
#include <map>
#include <list>

namespace GOAP
{
	class Action
	{
	public:
		Action();
		Action(const Action& other);
		~Action();

		virtual Action* Clone() = 0;
		virtual void Execute() = 0;
		virtual operator ActionType();

		std::list<Condition>::iterator GetFirstPrecondition();
		std::list<Condition>::iterator GetFirstEffect();

		Condition* operator == (Condition& cond);
		void CopySemanticsFromCondition(Condition& cond);

	protected:
		std::map<OperandSemanticType, Object*> m_args;
		std::list<Condition> m_preconds;
		std::list<Condition> m_effects;
	};
}
#endif