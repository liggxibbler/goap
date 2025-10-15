#ifndef _GOAP_OP_HAS_H_
#define _GOAP_OP_HAS_H_

#include "Operator.h"

namespace GOAP
{
	namespace Op
	{
		class Has : public Operator
		{
			virtual bool EvaluateOAVB(const Argument* params) const override;
			virtual bool EvaluateOAOAB(const Argument* params) const override;
			virtual bool EvaluateOOB(const Argument* params) const override;
		};
	}
}

#endif
