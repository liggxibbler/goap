#ifndef _GOAP_ACTION_H_
#define _GOAP_ACTION_H_

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
	protected:
		Object* m_params;
	};
}
#endif