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

			virtual bool Evaluate(Condition& cc);

			virtual bool EvaluateOAVB () = 0;
			virtual bool EvaluateOAOAB () = 0;
			virtual bool EvaluateOOB () = 0;

		protected:
			ConditionParameter* m_params;
			bool m_negate;
		};
	}
}

#endif