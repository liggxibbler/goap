#ifndef _GOAP_WAITFOR_H_
#define _GOAP_WAITFOR_H_

#define WAIT_TURNS 3

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class Room;

	class WaitFor : public Action
	{
	public:
		WaitFor();
		WaitFor(const WaitFor& other);
		WaitFor(Room* room, Agent* agent);
		~WaitFor();

		virtual operator ActionType();
		virtual WaitFor* Clone();

		virtual std::string Express(Agent* agent, Room* room) _CPP_11_OVERRIDE;
		virtual operator std::string() _CPP_11_OVERRIDE;

		virtual int Cost(RoomManager* rm) _CPP_11_OVERRIDE;
		virtual void Dispatch(int turn) _CPP_11_OVERRIDE;

	private:
		virtual Action* GetInstanceFromTuple(std::vector<Object*>& tuple) _CPP_11_OVERRIDE;

		virtual ExecutionStatus ExecuteWorkhorse(int turn);
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();

		int m_turns;
		Agent* m_agent;
		Object* m_dest;
		bool m_switch; // true for wait, false for do over
	};
}
#endif
