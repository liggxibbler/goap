#ifndef _GOAP_BLUGEON_H_
#define _GOAP_BLUGEON_H_

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class Blugeon : public Action
	{
	public:
		Blugeon();
		Blugeon(const Blugeon& other);
		~Blugeon();

		virtual operator ActionType();
		virtual Blugeon* Clone();		

		virtual std::string Express(Agent* agent) override;

	private:
		virtual ActionStatus ExecuteWorkhorse(int turn);
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();
	};
}
#endif