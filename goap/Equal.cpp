#include "Equal.h"

using namespace GOAP;
using namespace GOAP::Op;

bool Equal::EvaluateOAVB ()
{
	bool result;
	if ( m_objectPtrs[0]->GetAttrib(m_attribs[0]) == m_values[0] )
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
bool Equal::EvaluateOOAB ()
{
	bool result;
	if ( m_objectPtrs[0]->GetAttrib(m_attribs[0]) == m_objectPtrs[1]->GetAttrib(m_attribs[0]) )
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
bool Equal::EvaluateOAOAB ()
{
	bool result;
	if ( m_objectPtrs[0]->GetAttrib(m_attribs[0]) == m_objectPtrs[1]->GetAttrib(m_attribs[1]) )
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
bool Equal::EvaluateOOB ()
{
	bool result;
	if ( m_objectPtrs[0] == m_objectPtrs[1] )
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