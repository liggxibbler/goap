#ifndef _GOAP_OPERATORMANAGER_H_
#define _GOAP_OPERATORMANAGER_H_

#include <map>
#include "Common.h"

namespace GOAP
{
	class Operator;
	namespace Op
	{
		class OperatorManger
		{
		public:
			OperatorManger();
			OperatorManger(const OperatorManger& other);
			~OperatorManger();

			Operator* GetOperator(OperatorType ot);

		private:
			std::map<OperatorType, Operator*> m_mapOperator;
		};
	};
}

#endif