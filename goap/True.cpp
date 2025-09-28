#include "True.h"

using namespace GOAP;
using namespace GOAP::Op;

bool True::Evaluate(const Condition& condition) const
{
	return true;
}

bool True::EvaluateOAVB (const Argument* params, bool negate) const
{
	return true;
}
bool True::EvaluateOAOAB (const Argument* params, bool negate) const
{
	return true;
}
bool True::EvaluateOOB (const Argument* params, bool negate) const
{
	return true;
}