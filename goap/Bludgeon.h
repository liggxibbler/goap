#ifndef _GOAP_BLUDGEON_H_
#define _GOAP_BLUDGEON_H_

#include "Murder.h"
#include "Agent.h"

namespace GOAP
{
	class Bludgeon : public Murder
	{
	public:
		Bludgeon();
		Bludgeon(const Bludgeon& other);
		~Bludgeon();

		virtual operator ActionType();
		virtual Bludgeon* Clone();

		virtual std::string Express(Agent* agent, Room* room) _CPP_11_OVERRIDE;
		virtual operator std::string() _CPP_11_OVERRIDE;

	private:
		virtual void InitArgs() _CPP_11_OVERRIDE;
	};
}
#endif
