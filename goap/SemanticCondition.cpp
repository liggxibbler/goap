#include "SemanticCondition.h"

using namespace GOAP;

SemanticCondition::SemanticCondition()
{
}

SemanticCondition::SemanticCondition(SemanticCondition& other)
{
}

SemanticCondition::~SemanticCondition()
{
}

SemanticCondition::SemanticCondition(OperatorLayoutType layout, OperatorType oper) : AbstractCondition(layout, oper)
{
	m_topSemanticParam = 0;
	m_operandSemanticTypeParams = new OperandSemanticType[m_numObjectParams];
}

bool SemanticCondition::AddOperandSemanticTypeParam(OperandSemanticType ost)
{
	if(m_topSemanticParam < m_numObjectParams)
	{
		m_operandSemanticTypeParams[m_topSemanticParam++] = ost;
		return true;
	}
	else
	{
		//throw exception
		return false;
	}
}

OperandSemanticType SemanticCondition::GetSemanticByObjType(ObjectType ot)
{
	// Return the corresponding semantic for the provided object type
	//*** 
	//BAD_DESIGN_ALERT
	//***
	// This should return a list of candidates rather than a single one
	// but based on the design contract for now, that wouldn't be necessary
	
	for(int i = 0; i < m_numObjectParams; i++)
	{
		
		if(m_objectTypeParams[i] == ot)
		{
			return m_operandSemanticTypeParams[i];
		}
	}

	return OP_SEMANTIC_UNDEFINED;
}