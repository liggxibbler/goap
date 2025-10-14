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

		virtual ActionType GetActionType() const override;
		virtual Shoot* Clone();

		virtual std::string Express(const Agent* agent, const Room* room) const override;
		virtual std::string GetName() const override;

	private:
		virtual void InitArgs() override;
	};
}
#endif
