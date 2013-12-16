#include "Equal.h"

using namespace GOAP;
using namespace GOAP::Op;

bool Equal::EvaluateOAVB ()
{
	bool result;
	if(m_params[0].instance == 0)
	{
		// THROW EXCEPTION, ASSERTION FAILURE, SOMETHING!
		return false;
	}

	else if ( (*(m_params[0].instance))[m_params[0].attrib] == m_params[0].value )
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
bool Equal::EvaluateOAOAB ()
{
	bool result;
	if ( (*(m_params[0].instance))[m_params[0].attrib] == (*(m_params[1].instance))[m_params[1].attrib] )
	{
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}
bool Equal::EvaluateOOB ()
{
	bool result;
	if ( (m_params[0].instance) == (m_params[1].instance) )
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}