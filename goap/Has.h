#ifndef _GOAP_OP_HAS_H_
#define _GOAP_OP_HAS_H_

#include "Operator.h"

namespace GOAP
{
	namespace Op
	{
		class Has : public Operator
		{
			virtual bool EvaluateOAVB ();
			virtual bool EvaluateOAOAB ();
			virtual bool EvaluateOOB ();
		};
	}
}

#endif
