#include "GreaterThan.h"

using namespace GOAP;
using namespace GOAP::Op;

bool GreaterThan::EvaluateOAVB ()
{
	bool result;
	if ( m_objectPtrs[0]->GetAttrib(m_attribs[0]) > m_values[0] )
	{
		DUMP("attrib is" << m_objectPtrs[0]->GetAttrib(m_attribs[0]))
		DUMP("value is" << m_values[0])
		result = true;
	}
	else
	{
		result = false;
	}
	
	if(m_negate)
	{
		result = !result;
	}

	DUMP("result is" << result)

	return result;
}
bool GreaterThan::EvaluateOOAB ()
{
	bool result;
	if ( m_objectPtrs[0]->GetAttrib(m_attribs[0]) > m_objectPtrs[1]->GetAttrib(m_attribs[0]) )
	{
		result = true;
	}
	else
	{
		result = false;
	}
	
	if(m_negate)
	{
		result = !result;
	}

	return result;
}
bool GreaterThan::EvaluateOAOAB ()
{
	bool result;
	if ( m_objectPtrs[0]->GetAttrib(m_attribs[0]) > m_objectPtrs[1]->GetAttrib(m_attribs[1]) )
	{
		result = true;
	}
	else
	{
		result = false;
	}
	
	if(m_negate)
	{
		result = !result;
	}

	return result;
}
bool GreaterThan::EvaluateOOB ()
{
	// throw exception?
	return false;
}