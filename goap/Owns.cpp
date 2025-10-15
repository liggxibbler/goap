#include "Owns.h"

using namespace GOAP;
using namespace GOAP::Op;

bool Owns::EvaluateOOB (const Argument* params) const
{
	return params[1].instance->GetOwner() == params[0].instance;
}

bool Owns::EvaluateOAVB (const Argument* params) const
{
	return false;
}

bool Owns::EvaluateOAOAB (const Argument* params) const
{
	return false;
}