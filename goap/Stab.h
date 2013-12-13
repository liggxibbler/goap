#ifndef _GOAP_STAB_H_
#define _GOAP_STAB_H_

#include "Murder.h"
#include "Agent.h"

namespace GOAP
{
	class Stab : public Murder
	{
	public:
		Stab();
		Stab(const Stab& other);
		~Stab();

		virtual operator ActionType();
		virtual Stab* Clone();

		virtual std::string Express(Agent* agent, Room* room) _CPP_11_OVERRIDE;
		virtual operator std::string() _CPP_11_OVERRIDE;

	private:
		virtual void InitArgs() _CPP_11_OVERRIDE;
	};
}
#endif
