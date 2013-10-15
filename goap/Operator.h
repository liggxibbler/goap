#ifndef _GOAP_OPERATOR_H_
#define _GOAP_OPERATOR_H_

#include "Common.h"
#include "Object.h"
#include "ConcreteCondition.h"

namespace GOAP
{
	class Operator
	{
	public:
		Operator();
		Operator(const Operator& other);
		~Operator();

		// might make non-pure virtual, for exception handling...

		bool Evaluate(ConcreteCondition cc);

		virtual bool EvaluateOAVB () = 0;
		virtual bool EvaluateOOAB () = 0;
		virtual bool EvaluateOAOAB () = 0;
		virtual bool EvaluateOOB () = 0;

	protected:
		Object** m_objectPtrs;
		AttributeType* m_attribs;
		int* m_values;
		bool m_negate;
	};
};

#endif