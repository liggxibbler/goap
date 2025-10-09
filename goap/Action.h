#ifndef _GOAP_ACTION_H_
#define _GOAP_ACTION_H_

#include "Common.h"
#include "Object.h"
#include "Condition.h"
#include "Goal.h"
#include "OrderedPair.h"
#include "IExecutable.h"

#include <fstream>
#include <list>
#include <map>
#include <optional>
#include <string>
#include <sstream>
#include <vector>

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
		virtual ExecutionStatus Execute(const Op::OperatorManager& om, int turn) override;
		ExecutionStatus GetStatus();
		virtual operator ActionType() = 0;

		Goal* GetPreconds();
		Goal* GetGoal();

		virtual std::optional<const Condition*> GetCompatibleEffect(const Condition* cond) const;
		bool CopyArgInstancesFromCondition(const Condition& cond); // returns false if action's matching semantic doesn't have compatible type

		int GetPossibleInstances(Agent* agent, std::list<Action*>& result);

		Argument& GetArg(SemanticRole st);
		Argument& GetArg(ObjectType ot);
		Argument& GetArg(Object* obj);

		const Argument& GetArg(SemanticRole st) const;
		const Argument& GetArg(ObjectType ot) const;
		const Argument& GetArg(Object* obj) const;

		void Initialize();
		virtual void UpdateConditionInstances();

		virtual std::string Express(const Agent* agent, const Room* room) const = 0;

		virtual std::string GetName() const = 0;

		/*virtual int GetCost() = 0;
		virtual int GetRisk() = 0;*/

		virtual float Cost(const RoomManager& rm) = 0;

		bool EvaluatePreconditions(const Op::OperatorManager& om);
		bool EvaluateEffects(const Op::OperatorManager& om);

		bool IsLogged();
		void SetLogged();

		virtual void Debug();

		int GetNumWitness();

		void DumpToFile(int turn);

		static void OpenFile();
		static void CloseFile();

		virtual Goal* FollowupGoal();

		const std::list<Condition>& GetEffects() const;

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
		void CloneEffects(const Action* prototype);

		void UpdateEffectInstances();
		void UpdatePrecondInstances();

		virtual void Dispatch(int turn);

		virtual Action* GetInstanceFromTuple(std::vector<Object*>& tuple);

		std::list<Argument> m_args;
		//std::list<Condition> m_preconds;

		Goal* m_preconds = nullptr;

		std::list<Condition> m_effects;

		OrderedPair<Object*> m_orderedTuples;
		ExecutionStatus m_status = ExecutionStatus::NONE;

		int m_time = -1;
		int m_numWitness = -1;

		bool m_logged = false;
		static std::ofstream s_outFile;
	};
}
#endif
