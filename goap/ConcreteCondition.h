#ifndef _GOAP_CONCRETECONDITION_H_
#define _GOAP_CONCRETECONDITION_H_

#include "AbstractCondition.h"

namespace GOAP
{
	class ConcreteCondition : public AbstractCondition
	{
	private:
		std::list<Object*> m_objectParams;
	};
}

#endif