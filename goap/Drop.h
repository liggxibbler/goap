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

		virtual std::string Express(Agent* agent, Room* room) override;
		virtual operator std::string() override;

		virtual float Cost(const RoomManager& rm) override;

		virtual void UpdateConditionInstances() override;

		virtual bool MightSatisfy(Condition& cond); // XXX

		virtual void Debug() override;

		virtual void Dispatch(int turn) override;

	private:
		virtual ExecutionStatus ExecuteWorkhorse(int turn);
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();
	};
}

#endif

