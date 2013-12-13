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

		virtual std::string Express(Agent* agent, Room* room) _CPP_11_OVERRIDE;
		virtual operator std::string() _CPP_11_OVERRIDE;

	private:
		virtual void InitArgs() _CPP_11_OVERRIDE;
	};
}
#endif
