#include "Condition.h"
#include "OperatorManager.h"
#include "Operator.h"

using namespace GOAP;
using namespace Op;

Condition::Condition()
{
	m_params = nullptr;
	m_numParams = 0;
	m_layout = OperatorLayoutType::UNDEFINED;
	m_operatorType = OperatorType::UNDEFINED;
	m_negate = false;
	CreateArrays();
}

Condition::Condition(const Condition& other)
{
	m_layout = other.m_layout;
	m_negate = other.m_negate;
	m_numParams = other.m_numParams;
	m_operatorType = other.m_operatorType;

	m_params = nullptr;
	if(m_numParams != 0)
	{
		m_params = new Argument[m_numParams];
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
	case OperatorLayoutType::OAOAB:
		{
			m_numParams = 2;
			break;
		}
	case OperatorLayoutType::OAVB:
		{
			m_numParams = 1;
			break;
		}
	case OperatorLayoutType::OOB:
		{
			m_numParams = 2;
			break;
		}
	case OperatorLayoutType::UNDEFINED:
		{
			m_numParams = 0;
			break;
			//throw an exception
		}
	case OperatorLayoutType::TRUE:
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

	m_params = new Argument[m_numParams];

	return true;
}

bool Condition::operator == (const Condition& other) const
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
			static bool differentTypes;
			differentTypes = false;

			differentTypes = !m_params[i].MatchesTypeOf(other.m_params[i]);
			
			if(differentTypes || (m_params[i].attrib != other.m_params[i].attrib))
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

const Argument* Condition::GetParams()
{
	return m_params;
}

const Argument& Condition::operator[](int index) const
{
	return m_params[index];
}

Argument& Condition::GetParamByIndex(int index)
{
	return m_params[index];
}

int Condition::GetNumParams() const
{
	return m_numParams;
}

Argument* Condition::GetParamBySemantic(SemanticRole st)
{
	for(int i = 0; i < m_numParams; ++i)
	{
		if(m_params[i].semantic == st)
		{
			return &m_params[i];
		}
	}
	return nullptr;
}
Argument* Condition::GetParamByType(ObjectType ot)
{
	for(int i = 0; i < m_numParams; ++i)
	{
		if(m_params[i].type == ot)
		{
			return &m_params[i];
		}
	}
	return nullptr;
}
Argument* Condition::GetParamByInstance(Object* obj)
{
	for(int i = 0; i < m_numParams; ++i)
	{
		if(m_params[i].instance == obj)
		{
			return &m_params[i];
		}
	}

	return nullptr;
}

void Condition::CopySemantics(const Condition& other) const
{
	// This method is only called by the MightSatisfy method of Action
	// after it's verified that a Goal Condition and and effect are type
	// compatible,
	for(int i=0; i < m_numParams; i++)
	{
		m_params[i].semantic = other.m_params[i].semantic;
	}
}

bool Condition::EqualInstance(const Condition& other)
{
	// this is logically correct and consistent,
	// but maybe I should use a memory trick for quicker operation
	// should this prove too slow at any point

	bool result;
	result = ( (m_operatorType == other.m_operatorType) &&
		(m_layout == other.m_layout) &&
		(m_negate == other.m_negate) &&
		(m_numParams == other.m_numParams) );

	if(!result)
	{
		return false;
	}
	else
	{
		for(int i=0; i < m_numParams; i++)
		{
			if(m_params[i].instance != other.m_params[i].instance)
			{
				return false;
			}
		}
	}

	return true;
}