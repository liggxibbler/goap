#ifndef _GOAP_ACTION_H_
#define _GOAP_ACTION_H_

#include "Common.h"
#include "Object.h"
#include "Condition.h"
#include "Goal.h"
#include "OrderedPair.h"
#include "IExecutable.h"
#include <map>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

namespace GOAP
{
	class Agent;
	namespace Op
	{
		class OperatorManager;
	}

	class RoomManager;

	class Action : public IExecutable
	{
	public:
		Action();
		Action(const Action& other);
		~Action();

		virtual Action* Clone() = 0;
		virtual ExecutionStatus Execute(Op::OperatorManager* om, int turn) _CPP_11_OVERRIDE;
		ExecutionStatus GetStatus();
		virtual operator ActionType() = 0;

		Goal* GetPreconds();
		Goal* GetGoal();

		CondIter GetFirstEffect();
		CondIter GetLastEffect();

		CondParamIter GetFirstArg();
		CondParamIter GetLastArg();

		virtual bool MightSatisfy(Condition& cond); // XXX
		bool CopyArgsFromCondition(Condition& cond);

		int GetPossibleInstances(Agent* agent, std::list<Action*>& result);

		CondParamIter GetArg(SemanticRole st);
		CondParamIter GetArg(ObjectType ot);
		CondParamIter GetArg(Object* obj);

		void Initialize();
		virtual void UpdateConditionInstances();

		virtual std::string Express(Agent* agent, Room* room) = 0;

		virtual operator std::string() = 0;

		/*virtual int GetCost() = 0;
		virtual int GetRisk() = 0;*/

		static bool CompareCost(Action* a1, Action* a2);

		virtual int Cost(RoomManager* rm) = 0;

		bool EvaluatePreconditions(Op::OperatorManager* om);
		bool EvaluateEffects(Op::OperatorManager* om);

		bool IsLogged();
		void SetLogged();

		virtual void Debug();

		int GetNumWitness();

		void DumpToFile(int turn);

		static void OpenFile();
		static void CloseFile();

		virtual Goal* FollowupGoal();

	protected:

		virtual void InitArgs() = 0;
		virtual void InitPreconditions() = 0;
		virtual void InitEffects() = 0;

		virtual ExecutionStatus ExecuteWorkhorse(int turn) = 0;

		// XIBB make sure these can't run unless their respective data
		// has been initialized
		void CloneData(Action* prototype);
		void CloneArgs(Action* prototype);
		void ClonePreconds(Action* prototype);
		void CloneEffects(Action* prototype);

		void UpdateEffectInstances();
		void UpdatePrecondInstances();

		virtual void Dispatch(int turn);

		virtual Action* GetInstanceFromTuple(std::vector<Object*>& tuple);

		std::list<ConditionParameter> m_args;
		//std::list<Condition> m_preconds;

		Goal* m_preconds;

		std::list<Condition> m_effects;

		OrderedPair<Object*> m_orderedTuples;
		ExecutionStatus m_status;

		int m_time;
		int m_numWitness;

		bool m_logged;
		static std::ofstream s_outFile;
	};
}
#endif
