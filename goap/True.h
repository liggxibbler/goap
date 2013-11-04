#ifndef _GOAP_OP_TRUE_H_
#define _GOAP_OP_TRUE_H_

#include "Operator.h"

namespace GOAP
{
	namespace Op
	{
		class True : public Operator
		{
			virtual bool Evaluate();
			virtual bool EvaluateOAVB ();
			virtual bool EvaluateOAOAB ();
			virtual bool EvaluateOOB ();
		};
	}
}

#endif