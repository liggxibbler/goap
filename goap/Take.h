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

		virtual std::string Express(Agent* agent, Room* room) override;
		virtual operator std::string() override;

		virtual int Cost(RoomManager* rm) override;
		
		virtual void UpdateConditionInstances();

		virtual void Dispatch(int turn) override;
	private:
		virtual ExecutionStatus ExecuteWorkhorse(int turn);
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();
	};
}

#endif
