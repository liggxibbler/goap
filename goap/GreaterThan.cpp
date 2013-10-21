#include "GreaterThan.h"

using namespace GOAP;
using namespace GOAP::Op;

bool GreaterThan::EvaluateOAVB ()
{
	bool result;
	if ( (*(m_params[0].instance))[m_params[0].attrib] > m_params[0].value )
	{
		DUMP("attrib is " << m_params[0].instance->GetAttrib(m_params[0].attrib))
		DUMP("value is " << m_params[0].value)
		result = true;
	}
	else
	{
		result = false;
	}

	DUMP("result is " << result)

	return result;
}

bool GreaterThan::EvaluateOAOAB ()
{
	bool result;
	if ( (*(m_params[0].instance))[m_params[0].attrib] > (*(m_params[1].instance))[m_params[1].attrib] )
	{
		result = true;
	}
	else
	{
		result = false;
	}
	
	return result;
}
bool GreaterThan::EvaluateOOB ()
{
	// throw exception?
	return false;
}