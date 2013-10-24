#ifndef _GOAP_OPERATORMANAGER_H_
#define _GOAP_OPERATORMANAGER_H_

#include <map>
#include "Common.h"
#include "Operator.h"

namespace GOAP
{
	namespace Op
	{
		class OperatorManager
		{
		public:
			OperatorManager();
			OperatorManager(const OperatorManager& other);
			~OperatorManager();

			Operator* GetOperator(OperatorType ot);

		private:
			std::map<OperatorType, Operator*> m_mapOperator;
		};
	}
}

#endif