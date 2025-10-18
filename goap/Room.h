#ifndef _GOAP_ROOM_H_
#define _GOAP_ROOM_H_

#include <string>
#include <list>
#include <set>
#include "Common.h"
#include "Prop.h"

namespace GOAP
{
	class Agent;

	namespace Op
	{
		class OperatorManager;
	}

	class Room : public Object
	{
	public:
		Room();
		Room(const Room& other);
		Room(std::string&& name, RoomName rn, Object* owner = nullptr);
		~Room();

		void SetLeft(Room* left);
		void SetRight(Room* right);
		Room* GetLeft();
		Room* GetRight();

		Prop* AddObject(std::string name);
		void AddObject(Prop* obj);

		Agent* AddAgent(std::string name);
		void AddAgent(Agent* agent);

		//std::string GetName();

		const std::set<Prop*>& GetObjects() const;
		const std::set<Agent*>& GetAgents() const;

		RoomName GetType();

		virtual void Update(Planner & planner, int turn) override;

		void MarkForDeletion(Agent* agent);
		void MarkForAddition(Agent* agent);
		void UpdateAgentPositions();
		
		bool Contains(const Agent* agent) const;
		bool ContainsAnyExcept(const std::list<Agent*>& toExclude);

		virtual Object* Clone() const override;
		virtual void Examine() override;
		//virtual operator ObjectType ();

		virtual ObjectType GetCompoundType() const override;
		bool GetIsMurderRoom();

		void RemoveObject(Prop* obj);

		void ResetAgentUpdateFlags();

	private:
		void ClearMarkedAgents();
		void AddMarkedAgents();

		RoomName m_type;
		//std::string m_name;
		std::set<Prop*> m_objects;
		std::set<Agent*> m_agents;
		std::set<Agent*> m_markedForDeletion;
		std::set<Agent*> m_markedForAddition;

		int m_numAgents;		

		Room* m_left;
		Room* m_right;
	};
}

#endif
