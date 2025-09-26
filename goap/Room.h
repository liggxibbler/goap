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
		Room(std::string name, RoomName rn, Object* owner = nullptr);
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

		std::set<Prop*>::iterator GetFirstObject();
		std::set<Prop*>::iterator GetLastObject();

		std::set<Agent*>::iterator GetFirstAgent();
		std::set<Agent*>::iterator GetLastAgent();

		RoomName GetType();

		virtual bool Update(Op::OperatorManager* om, RoomManager* rm, int turn);

		void MarkForDeletion(Agent* agent);
		void MarkForAddition(Agent* agent);
		bool UpdateAgentPositions(Agent* agent, Agent* victim);

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
		bool m_murder;

		Room* m_left;
		Room* m_right;
	};
}

#endif
