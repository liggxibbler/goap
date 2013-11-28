#ifndef _GOAP_GOTO_H_
#define _GOAP_GOTO_H_

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class GoTo : public Action
	{
	public:
		GoTo();
		GoTo(const GoTo& other);
		~GoTo();

		virtual operator ActionType();
		virtual GoTo* Clone();

	private:
		virtual ActionStatus ExecuteWorkhorse();
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();
	};
}
#endif