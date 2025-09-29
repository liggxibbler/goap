#ifndef _GOAP_MURDER_H_
#define _GOAP_MURDER_H_

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class Murder : public Action
	{
	public:
		virtual float Cost(const RoomManager& rm) override;
		virtual ExecutionStatus ExecuteWorkhorse(int turn) override;

		void SetArguments(Agent* agent, Agent* patient, Object* instrument, Room* locative);
		virtual void Dispatch(int turn);

		virtual Goal* FollowupGoal();

	protected:
		virtual void InitArgs() override;
		virtual void InitPreconditions();
		virtual void InitEffects() override;
	};
}
#endif
