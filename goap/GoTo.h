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

		virtual std::string Express(Agent* agent, Room* room) _CPP_11_OVERRIDE;
		virtual operator std::string() _CPP_11_OVERRIDE;

		virtual int Cost(RoomManager* rm) _CPP_11_OVERRIDE;
		virtual void Dispatch(int turn) _CPP_11_OVERRIDE;

		virtual bool MightSatisfy(Condition& cond); // XXX

	private:
		virtual Action* GetInstanceFromTuple(std::vector<Object*>& tuple) _CPP_11_OVERRIDE;

		virtual ExecutionStatus ExecuteWorkhorse(int turn);
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();

		Agent* m_agent;
		Object* m_dest;
	};
}
#endif
