#include "Equal.h"

using namespace GOAP;
using namespace GOAP::Op;

bool Equal::EvaluateOAVB (const Argument* params) const
{
	return (*(params[0].instance))[params[0].attrib] == params[0].value;
}
bool Equal::EvaluateOAOAB (const Argument* params) const
{
	return (*(params[0].instance))[params[0].attrib] == (*(params[1].instance))[params[1].attrib];
}
bool Equal::EvaluateOOB (const Argument* params) const
{
	return (params[0].instance) == (params[1].instance);
}