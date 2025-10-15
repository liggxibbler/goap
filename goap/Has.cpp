#include "Has.h"

using namespace GOAP;
using namespace GOAP::Op;

bool Has::EvaluateOOB (const Argument* params) const
{
	if ( params[1].instance->GetAttrib(AttributeType::BEARER) == params[0].instance->GetID() )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Has::EvaluateOAVB (const Argument* params) const
{
	return false;
}

bool Has::EvaluateOAOAB (const Argument* params) const
{
	return false;
}
