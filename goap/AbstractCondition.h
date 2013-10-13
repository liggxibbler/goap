#ifndef _GOAP_ABSTRACT_CONDITION_H_
#define _GOAP_ABSTRACT_CONDITION_H_

#include "Common.h"
#include "Operator.h"
#include <queue>

namespace GOAP
{
	class AbstractCondition
	{
	public:
		AbstractCondition();
		AbstractCondition(const AbstractCondition& other);
		~AbstractCondition();
		
		AbstractCondition(OperatorLayoutType layout);

		bool operator == (AbstractCondition& other);

		void AddObjectTypeParam(ObjectType ot);
		void AddAttribParam(AttributeType at);

	private:
		OperatorLayoutType m_layout;
		Operator* m_operator;
		ObjectType* m_objectTypeParams;
		AttributeType* m_attribParams;
		bool m_negate;
	};
}

#endif