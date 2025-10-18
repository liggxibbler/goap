#include "Equal.h"

using namespace GOAP;
using namespace GOAP::Op;

bool Equal::EvaluateOAVB (const Argument* params) const
{
	return GetInstanceAttributeValue(params[0]) == params[0].value;
}
bool Equal::EvaluateOAOAB (const Argument* params) const
{
	return GetInstanceAttributeValue(params[0]) == GetInstanceAttributeValue(params[1]);
}
bool Equal::EvaluateOOB (const Argument* params) const
{
	return (params[0].instance) == (params[1].instance);
}