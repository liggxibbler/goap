#ifndef _GOAP_GOTO_H_
#define _GOAP_GOTO_H_

#include "Action.h"
#include "Agent.h"

namespace GOAP
{
	class Room;

	class GoTo : public Action
	{
	public:
		GoTo();
		GoTo(const GoTo& other);
		GoTo(Room* room, Agent* agent);
		~GoTo();

		virtual operator ActionType();
		virtual GoTo* Clone();

	private:
		virtual ActionStatus ExecuteWorkhorse();
		virtual void InitArgs();
		virtual void InitPreconditions();
		virtual void InitEffects();

		Agent* m_agent;
		Object* m_dest;
	};
}
#endif