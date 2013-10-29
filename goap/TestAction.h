#ifndef _GOAP_TESTACTION_H_
#define _GOAP_TESTACTION_H_

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class TestAction : public Action
	{
	public:
		TestAction();
		TestAction(const TestAction& other);
		~TestAction();

		virtual operator ActionType();
		virtual void Execute();
		virtual TestAction* Clone();
	private:
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();
	};
}
#endif