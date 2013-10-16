#include "AbstractCondition.h"

using namespace GOAP;

AbstractCondition::AbstractCondition()
{
	m_layout = OP_LAYOUT_TYPE_UNDEFINED;
	m_operatorType = OPER_TYPE_UNDEFINED;
	CreateArrays();
}

AbstractCondition::AbstractCondition(const AbstractCondition& other)
{
}
AbstractCondition::~AbstractCondition()
{
}
		
AbstractCondition::AbstractCondition(OperatorLayoutType layout, OperatorType oper)
{
	m_layout = layout;
	m_operatorType = oper;
	m_negate = false;
	CreateArrays();
}

bool AbstractCondition::CreateArrays()
{
	m_topAttribParams = 0;
	m_topObjectParams = 0;
	m_topValues = 0;

	switch(m_layout)
	{
	case OP_LAYOUT_TYPE_OAOAB:
		{
			m_numObjectParams = 2;
			m_numAttribParams = 2;
			m_numValues = 0;
			break;
		}
	case OP_LAYOUT_TYPE_OAVB:
		{
			m_numObjectParams = 1;
			m_numAttribParams = 1;
			m_numValues = 1;
			break;
		}
	case OP_LAYOUT_TYPE_OOAB:
		{
			m_numObjectParams = 2;
			m_numAttribParams = 1;
			m_numValues = 0;
			break;
		}
	case OP_LAYOUT_TYPE_OOB:
		{
			m_numObjectParams = 2;
			m_numAttribParams = 0;
			m_numValues = 0;
			break;
		}
	case OP_LAYOUT_TYPE_UNDEFINED:
		{
			m_numObjectParams = 0;
			m_numAttribParams = 0;
			m_numValues = 0;
			break;
			//throw an exception
		}
	default:
		{
			m_numObjectParams = 0;
			m_numAttribParams = 0;
			m_numValues = 0;
			//throw an exception
		}
	};

	m_objectTypeParams = new ObjectType[m_numObjectParams];
	if(m_objectTypeParams == 0) /*throw exeption*/return false;
	m_attribParams = new AttributeType[m_numAttribParams];
	if(m_attribParams == 0) /*throw exeption*/return false;
	m_values = new int[m_numValues];
	if(m_values == 0) /*throw exeption*/return false;

	return true;
}

bool AbstractCondition::operator == (AbstractCondition& other)
{
	// this is logically correct and consistent,
	// but maybe I should use a memory trick for quicker operation
	// should this prove too slow at any point

	bool result;
	result = m_operatorType == other.m_operatorType &&
		m_layout == other.m_layout &&
		m_negate == other.m_negate &&
		m_numObjectParams == other.m_numObjectParams &&						   
		m_numAttribParams == other.m_numAttribParams &&
		m_numValues == other.m_numValues;
	
	if(!result)
	{
		return false;
	}
	else
	{
		for(int i=0; i < m_numObjectParams; i++)
		{
			if(m_objectTypeParams[i] != other.m_objectTypeParams[i])
			{
				return false;
			}
		}
		
		for(int i=0; i < m_numAttribParams; i++)
		{
			if(m_attribParams[i] != other.m_attribParams[i])
			{
				return false;
			}
		}
		
		for(int i=0; i < m_numValues; i++)
		{
			if(m_values[i] != other.m_values[i])
			{
				return false;
			}
		}
	}

	return true;
}

bool AbstractCondition::AddObjectTypeParam(ObjectType ot)
{
	if(m_topObjectParams < m_numObjectParams)
	{
		m_objectTypeParams[m_topObjectParams++] = ot;
		return true;
	}
	else
	{
		return false;
	}
}

bool AbstractCondition::AddAttribParam(AttributeType at)
{
	if(m_topAttribParams < m_numAttribParams)
	{
		m_attribParams[m_topAttribParams++] = at;
		return true;
	}
	else
	{
		return false;
	}
}

bool AbstractCondition::AddValue(int val)
{
	if(m_topValues < m_numValues)
	{
		m_values[m_topValues++] = val;
		std::cout << "\nvalue" << m_values[m_topValues-1] << " added\n";
		return true;
	}
	else
	{
		return false;
	}
}


OperatorLayoutType AbstractCondition::GetOperatorLayoutType()
{
	return m_layout;
}

OperatorType AbstractCondition::GetOperatorType()
{
	return m_operatorType;
}

AttributeType* AbstractCondition::GetAttributes()
{
	return m_attribParams;
}

int* AbstractCondition::GetValues()
{
	return m_values;
}

bool AbstractCondition::GetNegate()
{
	return m_negate;
}

void AbstractCondition::SetNegate(bool value)
{
	m_negate = value;
}