#include "GreaterThan.h"

using namespace GOAP;
using namespace GOAP::Op;

bool GreaterThan::EvaluateOAVB (const Argument* params, bool negate) const
{
	bool result;
	if ( (*(params[0].instance))[params[0].attrib] > params[0].value )
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

bool GreaterThan::EvaluateOAOAB (const Argument* params, bool negate) const
{
	bool result;
	if ( (*(params[0].instance))[params[0].attrib] > (*(params[1].instance))[params[1].attrib] )
	{
		result = true;
	}
	else
	{
		result = false;
	}
	
	return result;
}
bool GreaterThan::EvaluateOOB (const Argument* params, bool negate) const
{
	// throw exception?
	return false;
}