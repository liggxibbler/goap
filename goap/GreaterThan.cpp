#include "GreaterThan.h"

using namespace GOAP;
using namespace GOAP::Op;

bool GreaterThan::EvaluateOAVB (const Argument* params) const
{
	return GetInstanceAttributeValue(params[0]) > params[0].value;
}

bool GreaterThan::EvaluateOAOAB (const Argument* params) const
{
	return GetInstanceAttributeValue(params[0]) > GetInstanceAttributeValue(params[1]);
}
bool GreaterThan::EvaluateOOB (const Argument* params) const
{
	// throw exception?
	return false;
}