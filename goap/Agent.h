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
	class RoomManager;
	class FactManager;

	namespace Op
	{
		class OperatorManager;
	}

	class Agent : public Object
	{
	public:

		friend class FactManager;

		Agent();
		Agent(std::string name);
		Agent(const Agent& other);
		~Agent();

		void InitializeCharacter(std::string name, Gender gender,
								 std::string backStory, float locationProbability[],
								 int room_count, std::string actions[], int action_count);

		const std::list<ActionType>& GetActions() const;

		std::map<int, Object*>::iterator FirstObject();
		std::map<int, Object*>::iterator LastObject();

		//virtual operator ObjectType ();
		Goal* GetGoal();
		void SetGoal(Goal* goal);

		void AddAction(ActionType at);

		bool Unify(ObjectType ot, std::vector<Object*>& result, bool strict);

		Plan* GetPlan(ActionManager* am, Op::OperatorManager* om);
		void See(Object* obj);
		void See(Room* room, bool deep = true);

		virtual ObjectType GetCompoundType() override;
		virtual bool Update(Op::OperatorManager* om, RoomManager* room, int turn) override;
		virtual void Examine() override;

		virtual bool CanBeMurderWeapon(); // XXX

		void Log(int turn, Action* action);

		bool GetMurder();
		void DoneMurder(bool flag);

		void Answer(Object* obj, QuestionType qt, int turn);
		void GiveStatement();
		void Lie(ActionRecord& ar, unsigned int& numStatement);

		RoomName GetNextRoom();

		virtual Object* Clone();

		Gender GetGender();

		void ResetUpdateFlag();

		void SetAsMurderer();
		void ResetMurdererFlag();
		bool IsMurderer();

		void SetAsVictim();
		void ResetVictimFlag();
		bool IsVictim();

		const float* GetProbabilities() const;

		void AddGoal(Goal* goal);

		bool PeekGoal();
		void PickCurrentGoal();

		std::vector<ActionRecord>::iterator GetFirstActionRecord();
		std::vector<ActionRecord>::iterator GetLastActionRecord();

	protected:

		void Interview();
		virtual void InitAttribMap() override;
		void SortGoals();

	protected:

		class GoalCpr
		{
		public:
			bool operator () (Goal* g1, Goal* g2)
			{
				return (g1->GetPriority() > g2->GetPriority());
			}
		} m_compare;

		Goal* m_currentGoal;
		std::list<Goal*> m_goals;
		std::list<ActionType> m_actions;

		int m_inventory;
		std::map<int, Object*> m_objects;

		static Planner* s_planner;
		Plan* m_plan;

		int m_height;
		int m_weight;
		Gender m_gender;
		std::string m_backStory;
		float m_roomProbabilities[NUMBER_OF_ROOMS];

		int m_isAlive;
		bool m_bDoneMurder;
		bool m_isVictim;
		bool m_isMurderer;

		bool m_updated;

		IExecutable* m_nextExecution;

		std::vector<ActionRecord> m_actionLog;
	};
}

#endif
