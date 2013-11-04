#include "OperatorManager.h"
#include "OperatorList.h"

using namespace GOAP;
using namespace GOAP::Op;

OperatorManager::OperatorManager()
{
	m_mapOperator[OPER_TYPE_EQUAL]			= new Equal();
	m_mapOperator[OPER_TYPE_GREATER_THAN]	= new GreaterThan();
	m_mapOperator[OPER_TYPE_TRUE]			= new True();
}

OperatorManager::OperatorManager(const OperatorManager& other)
{
}

OperatorManager::~OperatorManager()
{
	std::map<OperatorType, Operator*>::iterator iter;
	for ( iter = m_mapOperator.begin(); iter != m_mapOperator.end(); iter++)
	{
		delete (*iter).second;
	}
}

Operator* OperatorManager::GetOperator(OperatorType ot)
{
	return m_mapOperator[ot];
}