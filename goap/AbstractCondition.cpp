#include "AbstractCondition.h"
#include "OperatorManager.h"
#include "Operator.h"

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
	m_topParam = 0;	

	switch(m_layout)
	{
	case OP_LAYOUT_TYPE_OAOAB:
		{
			m_numParams = 2;
			break;
		}
	case OP_LAYOUT_TYPE_OAVB:
		{
			m_numParams = 1;
			break;
		}
	case OP_LAYOUT_TYPE_OOB:
		{
			m_numParams = 2;
			break;
		}
	case OP_LAYOUT_TYPE_UNDEFINED:
		{
			m_numParams = 0;
			break;
			//throw an exception
		}
	default:
		{
			m_numParams = 0;
			//throw an exception
		}
	};

	m_params = new ConditionParameter[m_numParams];
	
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
		m_numParams == other.m_numParams;
	
	if(!result)
	{
		return false;
	}
	else
	{
		for(int i=0; i < m_numParams; i++)
		{
			if(m_params[i].type != other.m_params[i].type ||
			m_params[i].attrib != other.m_params[i].attrib)
			{
				return false;
			}
		}		
	}

	return true;
}

OperatorLayoutType AbstractCondition::GetOperatorLayoutType()
{
	return m_layout;
}

OperatorType AbstractCondition::GetOperatorType()
{
	return m_operatorType;
}

bool AbstractCondition::GetNegate()
{
	return m_negate;
}

void AbstractCondition::SetNegate(bool value)
{
	m_negate = value;
}

bool AbstractCondition::Evaluate(Op::OperatorManger* om)
{
	Operator* oper = om->GetOperator(m_operatorType);
	return oper->Evaluate(this);
}

const ConditionParameter* AbstractCondition::GetParams()
{
	return m_params;
}

ConditionParameter& AbstractCondition::operator[](int index)
{
	return m_params[index];
}