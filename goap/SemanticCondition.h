#ifndef _GOAP_SEMANTIC_CONDITION_H_
#define _GOAP_SEMANTIC_CONDITION_H_

#include "AbstractCondition.h"

namespace GOAP
{
	class SemanticCondition : public AbstractCondition
	{
	public:
		SemanticCondition();
		SemanticCondition(SemanticCondition& other);
		~SemanticCondition();

		SemanticCondition(OperatorLayoutType layout, OperatorType oper);
		
		void AddOperandSemanticTypeParams(OperandSemanticType ost);
	private:
		OperandSemanticType* m_operandSemanticTypeParams;
	};
}

#endif