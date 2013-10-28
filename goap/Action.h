#ifndef _GOAP_ACTION_H_
#define _GOAP_ACTION_H_

#include "Common.h"
#include "Object.h"
#include "Condition.h"
#include <map>
#include <list>

namespace GOAP
{
	class Agent;

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
		std::list<Condition>::iterator GetLastPrecondition();
		
		std::list<Condition>::iterator GetFirstEffect();
		std::list<Condition>::iterator GetLastEffect();
		
		std::list<ConditionParameter>::iterator GetFirstArg();
		std::list<ConditionParameter>::iterator GetLastArg();

		bool MightSatisfy(Condition& cond);
		void CopyArgsFromCondition(Condition& cond);

		bool GetPossibleInstances(Agent* agent, std::list<Action*>& result);

		std::list<ConditionParameter>::iterator GetArgBySemantic(OperandSemanticType st);
		std::list<ConditionParameter>::iterator GetArgByType(ObjectType ot);
		std::list<ConditionParameter>::iterator GetArgByInstance(Object* obj);

	protected:
		virtual void InitArgs() = 0;
		virtual void InitPreconditions() = 0;
		virtual void InitEffects() = 0;

		std::list<ConditionParameter> m_args;
		std::list<Condition> m_preconds;
		std::list<Condition> m_effects;
	};
}
#endif