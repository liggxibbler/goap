#include "OperatorManager.h"
#include "Equal.h"
#include "GreaterThan.h"

using namespace GOAP;
using namespace GOAP::Op;

OperatorManger::OperatorManger()
{
	m_mapOperator[OPER_TYPE_EQUAL]			= new Equal();
	m_mapOperator[OPER_TYPE_GREATER_THAN]	= new GreaterThan();
}

OperatorManger::OperatorManger(const OperatorManger& other)
{
}

OperatorManger::~OperatorManger()
{
	std::map<OperatorType, Operator*>::iterator iter;
	for ( iter = m_mapOperator.begin(); iter != m_mapOperator.end(); iter++)
	{
		delete (*iter).second;
	}
}

Operator* OperatorManger::GetOperator(OperatorType ot)
{
	return m_mapOperator[ot];
}