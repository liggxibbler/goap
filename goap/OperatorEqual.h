#include "Operator.h"

namespace GOAP
{
	namespace Op
	{
		class Equal : public Operator
		{
			virtual bool EvaluateOAVB ();
			virtual bool EvaluateOOAB ();
			virtual bool EvaluateOAOAB ();
			virtual bool EvaluateOOB ();
		};
	}
}