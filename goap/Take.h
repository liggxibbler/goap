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

	private:
		virtual ActionStatus ExecuteWorkhorse();
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();
	};
}

#endif