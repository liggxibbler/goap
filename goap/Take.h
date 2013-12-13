#ifndef _GOAP_OP_TAKE_
#define _GOAP_OP_TAKE_

#include "Action.h"

namespace GOAP
{
	class Take : public Action
	{
	public:
		Take();
		Take(const Take& other);
		~Take();

		virtual operator ActionType();
		virtual Take* Clone();

		virtual std::string Express(Agent* agent, Room* room) _CPP_11_OVERRIDE;
		virtual operator std::string() _CPP_11_OVERRIDE;

		virtual int Cost(RoomManager* rm) _CPP_11_OVERRIDE;

	private:
		virtual ExecutionStatus ExecuteWorkhorse(int turn);
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();
	};
}

#endif
