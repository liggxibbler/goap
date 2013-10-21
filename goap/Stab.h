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
		Stab(Agent* subject, Agent* victim, Object* blade);
		Stab(const Stab& other);
		~Stab();

		virtual void Execute();
		virtual Stab* Clone();
	private:

	};
}
#endif