#ifndef _GOAP_ACTION_H_
#define _GOAP_ACTION_H_

#include "Common.h"
#include "Object.h"

namespace GOAP
{
	class Action
	{
	public:
		Action();
		Action(const Action& other);
		~Action();

		virtual void Execute() = 0;
		virtual operator ActionType();
	protected:
		Object* m_params;
	};
}
#endif