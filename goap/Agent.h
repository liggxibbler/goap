#ifndef _GOAP_AGENT_H_
#define _GOAP_AGENT_H_

//#include "ActionTemplate.h"
#include "Common.h"
#include "Object.h"
#include "Condition.h"
#include "Goal.h"
#include <list>
#include <vector>
#include <map>

namespace GOAP
{
	class Planner;
	class ActionManager;
	namespace Op
	{
		class OperatorManager;
	}

	class Agent : public Object
	{
	public:
		Agent();
		Agent(char* name);
		Agent(const Agent& other);
		~Agent();

		std::list<ActionType>::iterator FirstAction();
		std::list<ActionType>::iterator LastAction();

		std::map<int, Object*>::iterator FirstObject();
		std::map<int, Object*>::iterator LastObject();

		virtual operator ObjectType ();
		Goal* GetGoal();
		void SetGoal(Goal* goal);

		void AddAction(ActionType at);

		bool Unify(ObjectType ot, std::vector<Object*>& result);

		Goal* GetPlan(ActionManager* am, Op::OperatorManager* om);
		void See(Object* obj);

	protected:
		Goal* m_goal;
		std::list<ActionType> m_actions;
		std::map<int, Object*> m_objects;
		int m_height;
		int m_weight;
		int m_isAlive;
		Planner* m_planner;
	};
}

#endif