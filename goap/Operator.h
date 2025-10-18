#ifndef _GOAP_OPERATOR_H_
#define _GOAP_OPERATOR_H_

#include "Common.h"
#include "Object.h"
#include "Condition.h"

namespace GOAP
{
	namespace Op
	{
		class Operator
		{
		public:
			Operator();
			Operator(const Operator& other);
			~Operator();

			// might make non-pure virtual, for exception handling...

			virtual bool Evaluate(const Condition& cc) const;

			virtual bool EvaluateOAVB(const Argument* params) const = 0;
			virtual bool EvaluateOAOAB(const Argument* params) const = 0;
			virtual bool EvaluateOOB(const Argument* params) const = 0;

			static int& GetInstanceAttributeValue(const Argument& param);			

		protected:			
		};
	}
}

#endif