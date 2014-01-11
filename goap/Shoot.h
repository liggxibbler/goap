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

		virtual std::string Express(Agent* agent, Room* room) override;
		virtual operator std::string() override;

	private:
		virtual void InitArgs() override;
	};
}
#endif
