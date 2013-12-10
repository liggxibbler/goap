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
		virtual Stab* Clone();		

		virtual std::string Express(Agent* agent, Room* room) override;
		virtual operator std::string() override;

		virtual int Cost(RoomManager* rm) override;

	private:
		virtual ActionStatus ExecuteWorkhorse(int turn);
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();
	};
}
#endif