#include "Has.h"

using namespace GOAP;
using namespace GOAP::Op;

bool Has::EvaluateOOB ()
{
	if ( m_params[1].instance->GetAttrib(AttributeType::BEARER) == m_params[0].instance->GetID() )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Has::EvaluateOAVB ()
{
	return false;
}

bool Has::EvaluateOAOAB ()
{
	return false;
}
