#include "GreaterThan.h"

using namespace GOAP;
using namespace GOAP::Op;

bool GreaterThan::EvaluateOAVB (const Argument* params) const
{
	return (*(params[0].instance))[params[0].attrib] > params[0].value;
}

bool GreaterThan::EvaluateOAOAB (const Argument* params) const
{
	return (*(params[0].instance))[params[0].attrib] > (*(params[1].instance))[params[1].attrib];
}
bool GreaterThan::EvaluateOOB (const Argument* params) const
{
	// throw exception?
	return false;
}