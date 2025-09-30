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

		virtual std::string Express(const Agent* agent, const Room* room) const override;
		virtual operator std::string() override;

	private:
		virtual void InitArgs() override;
	};
}
#endif
