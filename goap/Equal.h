#ifndef _GOAP_OP_EQUAL_H_
#define _GOAP_OP_EQUAL_H_

#include "Operator.h"

namespace GOAP
{
	namespace Op
	{
		class Equal : public Operator
		{
			virtual bool EvaluateOAVB ();
			virtual bool EvaluateOAOAB ();
			virtual bool EvaluateOOB ();
		};
	}
}

#endif