#ifndef _GOAP_STRANGLE_H_
#define _GOAP_STRANGLE_H_

#include "Murder.h"
#include "Agent.h"

namespace GOAP
{
	class Strangle : public Murder
	{
	public:
		Strangle();
		Strangle(const Strangle& other);
		~Strangle();

		virtual operator ActionType();
		virtual Strangle* Clone();

		virtual std::string Express(Agent* agent, Room* room) override;
		virtual operator std::string() override;

	private:
		virtual void InitArgs() override;
	};
}
#endif
