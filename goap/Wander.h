#ifndef _GOAP_WANDER_H_
#define _GOAP_WANDER_H_

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class World;

	class Wander : public Action
	{
	public:
		Wander();
		Wander(World* world, Agent* agent, int turns);
		Wander(const Wander& other);
		~Wander();

		virtual operator ActionType();
		virtual Wander* Clone();

	private:
		virtual ActionStatus ExecuteWorkhorse();
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();

		int m_numTurns;
		World* m_world;
		Agent* m_agent;
	};
}
#endif