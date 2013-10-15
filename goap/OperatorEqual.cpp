#include "OperatorEqual.h"

using namespace GOAP;

bool OpEqual::EvaluateOAVB ()
{
	bool result;
	if ( m_objectPtrs[0]->GetAttrib(m_attribs[0]) == m_values[0] )
	{
		result = true;
	}
	else
	{
		result = false;
	}
	
	return m_negate == true ? result : !result;
}
bool OpEqual::EvaluateOOAB ()
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
	
	return m_negate == true ? result : !result;
}
bool OpEqual::EvaluateOAOAB ()
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
	
	return m_negate == true ? result : !result;
}
bool OpEqual::EvaluateOOB ()
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
	
	return m_negate == true ? result : !result;
}