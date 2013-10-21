#ifndef _GOAP_ACTION_H_
#define _GOAP_ACTION_H_

#include "Common.h"
#include "Object.h"
#include <map>

namespace GOAP
{
	class Action
	{
	public:
		Action();
		Action(const Action& other);
		~Action();

		virtual Action* Clone() = 0;
		virtual void Execute() = 0;
		virtual operator ActionType();
	protected:
		std::map<OperandSemanticType, Object*> m_semParams;
	};
}
#endif