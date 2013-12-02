#ifndef _GOAP_AGENT_H_
#define _GOAP_AGENT_H_

//#include "ActionTemplate.h"
#include "Common.h"
#include "Object.h"
#include "Condition.h"
#include "Goal.h"
#include "Plan.h"
#include "ActionRecord.h"
#include <list>
#include <vector>
#include <map>

namespace GOAP
{
	class Planner;
	class ActionManager;
	class Action;
	class Room;

	namespace Op
	{
		class OperatorManager;
	}

	class Agent : public Object
	{
	public:
		Agent();
		Agent(std::string name);
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

		bool Unify(int ot, std::vector<Object*>& result, bool strict);

		Plan* GetPlan(ActionManager* am, Op::OperatorManager* om);
		void See(Object* obj);
		void See(Room* room);

		virtual int GetCompoundType();
		virtual void Update(World* world, int turn) override;
		virtual void Examine();

		virtual bool CanBeMurderWeapon();

		void Log(int turn, Action* action);

		bool GetMurder();
		void DoneMurder(bool flag);

		void Answer(Object* obj, QuestionType qt, int turn);
		void GiveStatement();

	protected:
		void Interview();

		Goal* m_goal;
		std::list<ActionType> m_actions;
		std::map<int, Object*> m_objects;
		int m_height;
		int m_weight;
		int m_isAlive;
		Planner* m_planner;
		Plan* m_plan;

		bool m_bDoneMurder;

		IExecutable* m_nextExecution;

		std::vector<ActionRecord> m_actionLog;
	};
}

#endif