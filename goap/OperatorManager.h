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
			OperatorManager();
			OperatorManager(const OperatorManager& other);
			~OperatorManager();
		
		public:
			
			static OperatorManager* Instance();

			Operator* GetOperator(OperatorType ot);

		private:
			std::map<OperatorType, Operator*> m_mapOperator;
		};
	}
}

#endif