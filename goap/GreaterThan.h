#ifndef _GOAP_OP_GREATERTHAN_H_
#define _GOAP_OP_GREATERTHAN_H_

#include "Operator.h"

namespace GOAP
{
	namespace Op
	{
		class GreaterThan : public Operator
		{
			virtual bool EvaluateOAVB ();
			virtual bool EvaluateOAOAB ();
			virtual bool EvaluateOOB ();
		};
	}
}

#endif