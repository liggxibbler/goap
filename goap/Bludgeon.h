#ifndef _GOAP_BLUDGEON_H_
#define _GOAP_BLUDGEON_H_

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class Bludgeon : public Action
	{
	public:
		Bludgeon();
		Bludgeon(const Bludgeon& other);
		~Bludgeon();

		virtual operator ActionType();
		virtual Bludgeon* Clone();		

		virtual std::string Express(Agent* agent) override;
		virtual operator std::string() override;

		virtual int Cost() override;

	private:
		virtual ActionStatus ExecuteWorkhorse(int turn);
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();
	};
}
#endif