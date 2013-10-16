#include "ConcreteCondition.h"
#include "Operator.h"

using namespace GOAP;

ConcreteCondition::ConcreteCondition()
{
}

ConcreteCondition::ConcreteCondition(ConcreteCondition& other)
{
}

ConcreteCondition::~ConcreteCondition()
{
}

ConcreteCondition::ConcreteCondition(OperatorLayoutType layout, OperatorType oper) : AbstractCondition(layout, oper)
{
	m_topObjectPtrParam = 0;
	m_objectPtrParams = new Object*[m_numObjectParams];
}

Object* ConcreteCondition::GetObjPtrByObjType(ObjectType ot)
{
	// Return the corresponding object pointer for the provided object type
	//*** 
	//BAD_DESIGN_ALERT
	//***
	// This should return a list of candidates rather than a single one
	// but based on the design contract for now, that wouldn't be necessary
	
	for(int i = 0; i < m_numObjectParams; i++)
	{		
		if(m_objectTypeParams[i] == ot)
		{
			return m_objectPtrParams[i];
		}
	}
	
	return 0;
}

bool ConcreteCondition::AddObjectParam(Object* objptr)
{
	if(m_topObjectPtrParam < m_numObjectParams)
	{
		m_objectPtrParams[m_topObjectPtrParam++] = objptr;
		m_objectTypeParams[m_topObjectParams++] = (*objptr);
		DUMP("objptr" << m_objectPtrParams[m_topObjectPtrParam-1] << " added")
		return true;
	}
	else
	{
		//throw exception
		return false;
	}
}

bool ConcreteCondition::Evaluate(Op::OperatorManger* om)
{
	Operator* oper = om->GetOperator(m_operatorType);
	return oper->Evaluate(this);
}

Object** ConcreteCondition::GetObjects()
{
	return m_objectPtrParams;
}