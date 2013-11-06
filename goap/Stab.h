#ifndef _GOAP_STAB_H_
#define _GOAP_STAB_H_

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class Stab : public Action
	{
	public:
		Stab();
		Stab(const Stab& other);
		~Stab();

		virtual operator ActionType();
		virtual ActionStatus Execute();
		virtual Stab* Clone();		

	private:
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();
	};
}
#endif