#ifndef _GOAP_SEMANTIC_CONDITION_H_
#define _GOAP_SEMANTIC_CONDITION_H_

#include "AbstractCondition.h"

namespace GOAP
{
	class SemanticCondition : public AbstractCondition
	{
		void AddOperandSemanticTypeParams(OperandSemanticType ost);
	private:
		std::list<OperandSemanticType> m_operandSemanticTypeParams;
	};
}

#endif