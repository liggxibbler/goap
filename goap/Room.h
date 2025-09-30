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

		const std::set<Prop*>& GetObjects();
		const std::set<Agent*>& GetAgents();

		RoomName GetType();

		virtual bool Update(const ActionManager& actionManager, const Op::OperatorManager& om, const RoomManager& rm, int turn) override;

		void MarkForDeletion(Agent* agent);
		void MarkForAddition(Agent* agent);
		void UpdateAgentPositions();
		bool ContainsAnyExcept(const std::list<Agent*>& toExclude);
		bool ContainsMurderWitness(const std::list<Agent*>& toExclude);

		virtual Object* Clone();
		virtual void Examine() override;
		//virtual operator ObjectType ();

		virtual ObjectType GetCompoundType() override;
		bool GetMurder();

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
		bool m_isMurderRoom;

		Room* m_left;
		Room* m_right;
	};
}

#endif
