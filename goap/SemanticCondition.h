#ifndef _GOAP_SEMANTIC_CONDITION_H_
#define _GOAP_SEMANTIC_CONDITION_H_

#include "AbstractCondition.h"

namespace GOAP
{
	class SemanticCondition : public AbstractCondition
	{
		void AddOperandSemanticParam(OperandSemanticType ost);
	private:
		std::queue<OperandSemanticType> m_operandSemanticTypeParams;
	};
}

#endif