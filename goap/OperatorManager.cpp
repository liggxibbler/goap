#include "OperatorManager.h"
#include "OperatorList.h"

using namespace GOAP;
using namespace GOAP::Op;

OperatorManager::OperatorManager()
{
	m_mapOperator[OperatorType::EQUAL]			= new Equal();
	m_mapOperator[OperatorType::GREATER_THAN]	= new GreaterThan();
	m_mapOperator[OperatorType::TRUE]			= new True();
	m_mapOperator[OperatorType::OWNS]			= new Owns();
	m_mapOperator[OperatorType::HAS]			= new Has();
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