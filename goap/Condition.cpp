#include "Condition.h"
#include "OperatorManager.h"
#include "Operator.h"

using namespace GOAP;
using namespace Op;

Condition::Condition()
{
	m_params = NULL;
	m_numParams = 0;
	m_layout = OP_LAYOUT_TYPE_UNDEFINED;
	m_operatorType = OPER_TYPE_UNDEFINED;
	m_negate = false;
	CreateArrays();
}

Condition::Condition(const Condition& other)
{
	m_layout = other.m_layout;
	m_negate = other.m_negate;
	m_numParams = other.m_numParams;
	m_operatorType = other.m_operatorType;
	
	m_params = NULL;
	if(m_numParams != 0)
	{
		m_params = new ConditionParameter[m_numParams];
		for(int i = 0; i < m_numParams; i++)
		{
			m_params[i] = other.m_params[i];
		}
	}

	m_topParam = 0;
}

Condition::~Condition()
{
}
		
Condition::Condition(OperatorLayoutType layout, OperatorType oper) :
m_layout(layout), m_operatorType(oper), m_negate(false)
{
	CreateArrays();
}

bool Condition::CreateArrays()
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
	case OP_LAYOUT_TYPE_TRUE:
		{
			m_numParams = 0;
			break;
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

bool Condition::operator == (Condition& other)
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

OperatorLayoutType Condition::GetOperatorLayoutType()
{
	return m_layout;
}

OperatorType Condition::GetOperatorType()
{
	return m_operatorType;
}

bool Condition::GetNegate()
{
	return m_negate;
}

void Condition::SetNegate(bool value)
{
	m_negate = value;
}

bool Condition::Evaluate(Op::OperatorManager* om)
{
	Operator* oper = om->GetOperator(m_operatorType);
	return oper->Evaluate(*this);
}

const ConditionParameter* Condition::GetParams()
{
	return m_params;
}

ConditionParameter& Condition::operator[](int index)
{
	return m_params[index];
}

int Condition::GetNumParams()
{
	return m_numParams;
}

ConditionParameter* Condition::GetParamBySemantic(OperandSemanticType st)
{
	for(int i = 0; i < m_numParams; ++i)
	{
		if(m_params[i].semantic == st)
		{
			return &m_params[i];
		}
	}
	return NULL;
}
ConditionParameter* Condition::GetParamByType(ObjectType ot)
{
	for(int i = 0; i < m_numParams; ++i)
	{
		if(m_params[i].type == ot)
		{
			return &m_params[i];
		}
	}
	return NULL;
}
ConditionParameter* Condition::GetParamByInstance(Object* obj)
{
	for(int i = 0; i < m_numParams; ++i)
	{
		if(m_params[i].instance == obj)
		{
			return &m_params[i];
		}
	}

	return NULL;
}

void Condition::CopySemantics(Condition& other)
{
	// This method is only called by the MightSatisfy method of Action
	// after it's verified that a Goal Condition and and effect are type
	// compatible,
	for(int i=0; i < m_numParams; i++)
	{
		other.m_params[i].semantic = m_params[i].semantic;
	}
}