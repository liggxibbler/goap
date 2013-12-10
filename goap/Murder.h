#ifndef _GOAP_MURDER_H_
#define _GOAP_MURDER_H_

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class Murder : public Action
	{
	public:
		virtual int Cost(RoomManager* rm) override;

	protected:
		virtual void InitArgs() override;
		virtual void InitPreconditions();
		virtual void InitEffects() override;
	};
}
#endif