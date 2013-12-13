#ifndef _GOAP_SHOOT_H_
#define _GOAP_SHOOT_H_

#include "Murder.h"
#include "Agent.h"

namespace GOAP
{
	class Shoot : public Murder
	{
	public:
		Shoot();
		Shoot(const Shoot& other);
		~Shoot();

		virtual operator ActionType();
		virtual Shoot* Clone();

		virtual std::string Express(Agent* agent, Room* room) _CPP_11_OVERRIDE;
		virtual operator std::string() _CPP_11_OVERRIDE;

	private:
		virtual void InitArgs() _CPP_11_OVERRIDE;
	};
}
#endif
