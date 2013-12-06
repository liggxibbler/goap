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

		void InitializeCharacter(std::string name, Gender gender, 
								 std::string backStory, int locationProbability[], 
								 bool canStab, bool canStrangle, bool canShoot, 
								 bool canBludgeon, int height, int weight);

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
		virtual bool Update(World* world, int turn) override;
		virtual void Examine();

		virtual bool CanBeMurderWeapon();

		void Log(int turn, Action* action);

		bool GetMurder();
		void DoneMurder(bool flag);

		void Answer(Object* obj, QuestionType qt, int turn);
		void GiveStatement();

		RoomName GetNextRoom();

		virtual Object* Clone();

	protected:
		void Interview();

		Goal* m_goal;
		std::list<ActionType> m_actions;
		std::map<int, Object*> m_objects;	
		Planner* m_planner;
		Plan* m_plan;

		int m_height;
		int m_weight;
		Gender m_gender;
		std::string m_backStory;
		int m_locationProbability[NUMBER_OF_ROOMS];

		int m_isAlive;
		bool m_bDoneMurder;
		bool m_isVictim;
		bool m_isMurderer;

		IExecutable* m_nextExecution;

		std::vector<ActionRecord> m_actionLog;
	};
}

#endif