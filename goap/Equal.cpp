#include "Equal.h"

using namespace GOAP;
using namespace GOAP::Op;

bool Equal::EvaluateOAVB (const Argument* params) const
{
	bool result;
	if(params[0].instance == 0)
	{
		// THROW EXCEPTION, ASSERTION FAILURE, SOMETHING!
		return false;
	}

	else if ( (*(params[0].instance))[params[0].attrib] == params[0].value )
	{
		DUMP("attrib is " << params[0].instance->GetAttrib(params[0].attrib))
		DUMP("value is " << params[0].value)
		result = true;
	}
	else
	{
		result = false;
	}

	DUMP("result is " << result)

	return result;
}
bool Equal::EvaluateOAOAB (const Argument* params) const
{
	bool result;
	if ( (*(params[0].instance))[params[0].attrib] == (*(params[1].instance))[params[1].attrib] )
	{
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}
bool Equal::EvaluateOOB (const Argument* params) const
{
	bool result;
	if ( (params[0].instance) == (params[1].instance) )
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}