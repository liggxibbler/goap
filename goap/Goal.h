#ifndef _GOAP_GOAL_H_
#define _GOAP_GOAL_H_

#include "Condition.h"
#include "OperatorManager.h"
#include <list>

namespace GOAP
{
	typedef std::list<Condition>::iterator CondIter;
	typedef std::list<Argument>::iterator ArgIter;

	class Action;
	class Plan;

	class Goal
	{
	public:

		Goal();
		Goal(Goal* parent, Action* action, bool negate);
		//Goal(const Goal& other);
		~Goal();

		bool Evaluate(Op::OperatorManager* om);
		bool IsConsistent(Op::OperatorManager* om);/*?*/

		void AddChild(Goal* child);
		Goal* GetParent();
		std::list<Goal*>::iterator GetFirstChild();

		void AddCondition(Condition& cond);
		void RemoveCondition(const Condition& cond);
		void CleanSemanticInstances();

		CondIter GetFirstCondition();
		CondIter GetLastCondition();
		const std::list<GOAP::Condition>& GetConditions() const;

		//bool operator < (Goal& other);

		int GetDepth();
		void SetDepth(int depth);

		Goal* Combine(Goal* other);

		Goal* Clone();

		void SetAction(Action* action);
		void SetParent(Goal* parent);

		Action* GetAction();
		void ClearChildren();

		int GetNumConditions();
		int GetCost();
		void SetCost(int cost);

		Plan* GetPlan();
		int GetPriority();
		void SetPriority(int priority);

	private:
		Goal* m_parent;						// XIBB Theoretically, there can be multiple parents. So be careful.
											// i.e. individual goal nodes can be reached from more than on higher goal
		Action* m_action;					// The action that would change the satet to the parent state
		std::list<Condition> m_conditions;	// Conditions of the goal
		std::list<Goal*> m_children;		// States that can reach this state
		bool m_negate;						// Whether or not to complement after evaluation

		int m_depth;						// How many goals are stacked on top?
		int m_cost;							// Minimum cost so far from this state to ultimate goal
		Plan* m_plan;
		int m_priority;						// Used to sort goal list
	};
}

#endif