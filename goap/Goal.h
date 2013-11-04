#ifndef _GOAP_GOAL_H_
#define _GOAP_GOAL_H_

#include "Condition.h"
#include "OperatorManager.h"
#include <list>

namespace GOAP
{
	typedef std::list<Condition>::iterator CondIter;
	typedef std::list<ConditionParameter>::iterator CondParamIter;

	class Action;

	class Goal
	{
	public:

		Goal();
		Goal(Goal* parent, Action* action, bool negate);
		Goal(const Goal& other);
		~Goal();

		bool Evaluate(Op::OperatorManager* om);
		bool IsConsistent(Op::OperatorManager* om);/*?*/

		void AddChild(Goal* child);
		Goal* GetParent();
		std::list<Goal*>::iterator GetFirstChild();

		void AddCondition(Condition& cond);
		void RemoveCondition(Condition& cond);		

		CondIter GetFirstCondition();
		CondIter GetLastCondition();

		//bool operator < (Goal& other);

		int GetDepth();

		Goal* Combine(Goal* other);

		Goal* Clone();

		void SetAction(Action* action);
		void SetParent(Goal* parent);

	private:
		Goal* m_parent;						// XIBB Theoretically, there can be multiple parents. So be careful.
											// i.e. individual goal nodes can be reached from more than on higher goal
		Action* m_action;					// The action that would change the satet to the parent state
		std::list<Condition> m_conditions;	// Conditions of the goal
		std::list<Goal*> m_children;		// States that can reach this state
		bool m_negate;						// Whether or not to complement after evaluation

		int m_depth;						// How many goals are stacked on top?
		int m_cost;							// Minimum cost so far from this state to ultimate goal
	};
}

#endif