#ifndef _GOAP_WAITFOR_H_
#define _GOAP_WAITFOR_H_

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

		virtual std::string Express(Agent* agent) override;
		virtual operator std::string() override;

		virtual int Cost(RoomManager* rm) override;
		virtual void Dispatch(int turn) override;
	private:
		virtual ActionStatus ExecuteWorkhorse(int turn);
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();

		Agent* m_agent;
		Object* m_dest;
	};
}
#endif