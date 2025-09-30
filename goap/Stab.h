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

		virtual std::string Express(const Agent* agent, const Room* room) const override;
		virtual operator std::string() override;

	private:
		virtual void InitArgs() override;
	};
}
#endif
