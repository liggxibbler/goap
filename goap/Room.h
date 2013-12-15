#ifndef _GOAP_ROOM_H_
#define _GOAP_ROOM_H_

#include <string>
#include <list>
#include <set>
#include "Common.h"
#include "STUFF.h"

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
		Room(std::string name, RoomName rn, Object* owner = NULL);
		~Room();

		void SetLeft(Room* left);
		void SetRight(Room* right);
		Room* GetLeft();
		Room* GetRight();

		STUFF* AddObject(std::string name);
		void AddObject(STUFF* obj);

		Agent* AddAgent(std::string name);
		void AddAgent(Agent* agent);

		//std::string GetName();

		std::list<STUFF*>::iterator GetFirstObject();
		std::list<STUFF*>::iterator GetLastObject();

		std::set<Agent*>::iterator GetFirstAgent();
		std::set<Agent*>::iterator GetLastAgent();

		RoomName GetType();

		virtual bool Update(Op::OperatorManager* om, RoomManager* rm, int turn);

		void MarkForDeletion(Agent* agent);
		void MarkForAddition(Agent* agent);
		bool UpdateAgentPositions(Agent* agent, Agent* victim);

		virtual Object* Clone();
		virtual void Examine() _CPP_11_OVERRIDE;
		virtual operator ObjectType ();

		virtual int GetCompoundType() _CPP_11_OVERRIDE;
		bool GetMurder();

		void RemoveObject(STUFF* obj);

		void ResetAgentUpdateFlags();

	private:
		void ClearMarkedAgents();
		void AddMarkedAgents();

		RoomName m_type;
		//std::string m_name;
		std::list<STUFF*> m_objects;
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
