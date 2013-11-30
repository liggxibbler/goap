#ifndef _GOAP_WANDER_H_
#define _GOAP_WANDER_H_

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class Wander : public Action
	{
	public:
		Wander();
		Wander(const GoTo& other);
		~Wander();

		virtual operator ActionType();
		virtual Wander* Clone();

	private:
		virtual ActionStatus ExecuteWorkhorse();
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();

		int m_numTurns;
		int m_currentTurn;

	};
}
#endif