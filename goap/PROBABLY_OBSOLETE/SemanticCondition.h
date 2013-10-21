#ifndef _GOAP_SEMANTIC_CONDITION_H_
#define _GOAP_SEMANTIC_CONDITION_H_

#include "ConcreteCondition.h"

namespace GOAP
{
	class SemanticCondition : public ConcreteCondition
	{
	public:
		SemanticCondition();
		SemanticCondition(SemanticCondition& other);
		~SemanticCondition();

		SemanticCondition(OperatorLayoutType layout, OperatorType oper);
		
		bool AddOperandSemanticTypeParam(OperandSemanticType ost);

		OperandSemanticType GetSemanticByObjType(ObjectType ot);

	private:
		OperandSemanticType* m_operandSemanticTypeParams;
		int m_topSemanticParam;
	};
}

#endif