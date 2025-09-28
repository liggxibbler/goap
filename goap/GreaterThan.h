#ifndef _GOAP_OP_GREATERTHAN_H_
#define _GOAP_OP_GREATERTHAN_H_

#include "Operator.h"

namespace GOAP
{
	namespace Op
	{
		class GreaterThan : public Operator
		{
			virtual bool EvaluateOAVB (const Argument* params, bool negate) const override;
			virtual bool EvaluateOAOAB (const Argument* params, bool negate) const override;
			virtual bool EvaluateOOB (const Argument* params, bool negate) const override;
		};
	}
}

#endif