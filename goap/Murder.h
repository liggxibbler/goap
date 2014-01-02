#ifndef _GOAP_MURDER_H_
#define _GOAP_MURDER_H_

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class Murder : public Action
	{
	public:
		virtual int Cost(RoomManager* rm) _CPP_11_OVERRIDE	;
		virtual ExecutionStatus ExecuteWorkhorse(int turn) _CPP_11_OVERRIDE;

		void SetArguments(Agent* agent, Agent* patient, Object* instrument, Room* locative);
		virtual void Dispatch(int turn);

		virtual Goal* FollowupGoal();

	protected:
		virtual void InitArgs() _CPP_11_OVERRIDE;
		virtual void InitPreconditions();
		virtual void InitEffects() _CPP_11_OVERRIDE;
	};
}
#endif
