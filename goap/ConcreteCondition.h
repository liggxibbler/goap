#ifndef _GOAP_CONCRETE_CONDITION_H_
#define _GOAP_CONCRETE_CONDITION_H_

#include "AbstractCondition.h"
#include "Object.h"

namespace GOAP
{
	class ConcreteCondition : public AbstractCondition
	{
	public:
		ConcreteCondition();
		ConcreteCondition(ConcreteCondition& other);
		~ConcreteCondition();

		ConcreteCondition(OperatorLayoutType layout, OperatorType oper);

		Object* GetObjPtrByObjType(ObjectType ot);

		bool AddObjectParam(Object* objptr);
		bool Evaluate();

		// ***
		// BAD_DESIGN_ALERT
		// **
		// some of these need to be moved to AbstractAction for consistency
		Object** GetObjects();

	private:
		Object** m_objectPtrParams;
		int m_topObjectPtrParam;
	};
}

#endif