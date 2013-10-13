#ifndef _GOAP_CONCRETE_CONDITION_H_
#define _GOAP_CONCRETE_CONDITION_H_

#include "AbstractCondition.h"

namespace GOAP
{
	class ConcreteCondition : public AbstractCondition
	{
	public:
		ConcreteCondition();
		ConcreteCondition(ConcreteCondition& other);
		~ConcreteCondition();

		ConcreteCondition(OperatorLayoutType layout);

		void AddObjectParam(Object*);
		bool Evaluate();
	private:
		Object* m_objectParams;
	};
}

#endif