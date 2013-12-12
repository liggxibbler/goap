#ifndef _GOAP_GOTO_H_
#define _GOAP_GOTO_H_

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class Room;

	class GoTo : public Action
	{
	public:
		GoTo();
		GoTo(const GoTo& other);
		GoTo(Room* room, Agent* agent);
		~GoTo();

		virtual operator ActionType();
		virtual GoTo* Clone();

		virtual std::string Express(Agent* agent, Room* room) override;
		virtual operator std::string() override;

		virtual int Cost(RoomManager* rm) override;
		virtual void Dispatch(int turn) override;

	private:
		virtual Action* GetInstanceFromTuple(std::vector<Object*>& tuple) override;

		virtual ExecutionStatus ExecuteWorkhorse(int turn);
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();

		Agent* m_agent;
		Object* m_dest;
	};
}
#endif