#ifndef _GOAP_SHOOT_H_
#define _GOAP_SHOOT_H_

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class Shoot : public Action
	{
	public:
		Shoot();
		Shoot(const Shoot& other);
		~Shoot();

		virtual operator ActionType();
		virtual Shoot* Clone();		

		virtual std::string Express(Agent* agent) override;

	private:
		virtual ActionStatus ExecuteWorkhorse(int turn);
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();
	};
}
#endif