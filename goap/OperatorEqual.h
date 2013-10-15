#ifndef _GOAP_OPEQUAL_H_
#define _GOAP_OPEQUAL_H_

#include "Operator.h"

namespace GOAP
{
	class OpEqual : public Operator
	{
		virtual bool EvaluateOAVB ();
		virtual bool EvaluateOOAB ();
		virtual bool EvaluateOAOAB ();
		virtual bool EvaluateOOB ();
	};
}

#endif