#ifndef _GOAP_OP_TRUE_H_
#define _GOAP_OP_TRUE_H_

#include "Operator.h"

namespace GOAP
{
	namespace Op
	{
		class True : public Operator
		{
			virtual bool Evaluate(const Condition& cc) const override;
			virtual bool EvaluateOAVB(const Argument* params) const override;
			virtual bool EvaluateOAOAB(const Argument* params) const override;
			virtual bool EvaluateOOB(const Argument* params) const override;
		};
	}
}

#endif