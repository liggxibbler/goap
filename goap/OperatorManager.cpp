#include "OperatorManager.h"
#include "OperatorList.h"

using namespace GOAP;
using namespace GOAP::Op;

OperatorManager::OperatorManager()
{
	m_mapOperator[OPERATOR_EQUAL]			= new Equal();
	m_mapOperator[OPERATOR_GREATER_THAN]	= new GreaterThan();
	m_mapOperator[OPERATOR_TRUE]			= new True();
	m_mapOperator[OPERATOR_OWNS]			= new Owns();
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

OperatorManager* OperatorManager::Instance()
{
	static OperatorManager om;
	return &om;
}