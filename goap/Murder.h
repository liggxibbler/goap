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
	protected:
		virtual void InitArgs() _CPP_11_OVERRIDE;
		virtual void InitPreconditions();
		virtual void InitEffects() _CPP_11_OVERRIDE;
	};
}
#endif