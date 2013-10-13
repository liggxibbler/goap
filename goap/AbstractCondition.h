#ifndef _GOAP_ABSTRACTCONDITION_H_
#define _GOAP_ABSTRACTCONDITION_H_

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

		void AddObjectParam(ObjectType ot);
		void AddAttribParam(AttributeType at);

	private:
		OperatorLayoutType m_layout;
		Operator* m_operator;
		std::queue<ObjectType> m_objectTypeParams;
		std::queue<AttributeType> m_attribParams;
	};
}

#endif