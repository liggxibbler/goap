#ifndef _GOAP_OP_OWNS_H_
#define _GOAP_OP_OWNS_H_

#include "Operator.h"

namespace GOAP
{
	namespace Op
	{
		class Owns : public Operator
		{
			virtual bool EvaluateOAVB ();
			virtual bool EvaluateOAOAB ();
			virtual bool EvaluateOOB ();
		};
	}
}

#endif