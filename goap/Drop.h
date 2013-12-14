#ifndef _GOAP_OP_DROP_
#define _GOAP_OP_DROP_

#include "Action.h"

namespace GOAP
{
	class Drop : public Action
	{
	public:
		Drop();
		Drop(const Drop& other);
		~Drop();

		virtual operator ActionType();
		virtual Drop* Clone();

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

