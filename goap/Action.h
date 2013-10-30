#ifndef _GOAP_ACTION_H_
#define _GOAP_ACTION_H_

#include "Common.h"
#include "Object.h"
#include "Condition.h"
#include "Goal.h"
#include "OrderedPair.h"
#include <map>
#include <list>
#include <vector>

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

		Goal* GetPreconds();		
		Goal* GetGoal();

		CondIter GetFirstEffect();
		CondIter GetLastEffect();
		
		CondParamIter GetFirstArg();
		CondParamIter GetLastArg();

		bool MightSatisfy(Condition& cond);
		void CopyArgsFromCondition(Condition& cond);

		bool GetPossibleInstances(Agent* agent, std::list<Action*>& result);

		CondParamIter GetArgBySemantic(OperandSemanticType st);
		CondParamIter GetArgByType(ObjectType ot);
		CondParamIter GetArgByInstance(Object* obj);

		void Initialize();
		
	protected:

		virtual void InitArgs() = 0;
		virtual void InitPreconditions() = 0;
		virtual void InitEffects() = 0;

		// XIBB make sure these can't run unless their respective data
		// has been initialized
		void CloneData(Action* prototype);
		void CloneArgs(Action* prototype);
		void ClonePreconds(Action* prototype);
		void CloneEffects(Action* prototype);

		Action* GetInstanceFromTuple(std::vector<Object*>);

		std::list<ConditionParameter> m_args;
		//std::list<Condition> m_preconds;
		
		Goal* m_preconds;

		std::list<Condition> m_effects;

		OrderedPair<Object*> m_orderedTuples;
	};
}
#endif