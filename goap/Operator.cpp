#include "Operator.h"

using namespace GOAP;
using namespace Op;

Operator::Operator()
{}

Operator::Operator(const Operator& other)
{}

Operator::~Operator()
{}

// might make non-pure virtual, for exception handling...

bool Operator::Evaluate(Condition& ac)
{
	bool result;
	
	if( ac.GetNumParams() != 0)
	{
		m_params = (ConditionParameter*) ac.GetParams();
	}
	
	m_negate = ac.GetNegate();

	switch(ac.GetOperatorLayoutType())
	{
	case OP_LAYOUT_TYPE_OAOAB:
		{
			result = EvaluateOAOAB();
			break;
		}
	case OP_LAYOUT_TYPE_OAVB:
		{
			result = EvaluateOAVB();
			break;
		}
	case OP_LAYOUT_TYPE_OOB:
		{
			result = EvaluateOOB();
			break;
		}
	case OP_LAYOUT_TYPE_TRUE:
		{
			result = true;
			break;
		}
	case OP_LAYOUT_TYPE_UNDEFINED:
		{
			//throw exception
			result = false;
			break;
		}
	default:
		{
			//throw different exception
			result = false;
			break;
		}
	};
	
	if(m_negate)
		result = !result;

	return result;
}