#include "Owns.h"

using namespace GOAP;
using namespace GOAP::Op;

bool Owns::EvaluateOOB (const Argument* params) const
{
	if (params[1].instance == 0)
	{
		return false;
	}
	else if ( params[1].instance->GetOwner() == params[0].instance )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Owns::EvaluateOAVB (const Argument* params) const
{
	return false;
}

bool Owns::EvaluateOAOAB (const Argument* params) const
{
	return false;
}