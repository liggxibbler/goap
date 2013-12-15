#include "Owns.h"

using namespace GOAP;
using namespace GOAP::Op;

bool Owns::EvaluateOOB ()
{
	if (m_params[1].instance == 0)
	{
		return false;
	}
	else if ( m_params[1].instance->GetOwner() == m_params[0].instance )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Owns::EvaluateOAVB ()
{
	return false;
}

bool Owns::EvaluateOAOAB ()
{
	return false;
}