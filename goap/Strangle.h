#ifndef _GOAP_STRANGLE_H_
#define _GOAP_STRANGLE_H_

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class Strangle : public Action
	{
	public:
		Strangle();
		Strangle(const Strangle& other);
		~Strangle();

		virtual operator ActionType();
		virtual Strangle* Clone();		

		virtual std::string Express(Agent* agent) override;
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