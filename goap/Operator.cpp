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
		m_params = (Argument*) ac.GetParams();
	}
	
	m_negate = ac.GetNegate();

	switch(ac.GetOperatorLayoutType())
	{
	case OperatorLayoutType::OAOAB:
		{
			result = EvaluateOAOAB();
			break;
		}
	case OperatorLayoutType::OAVB:
		{
			result = EvaluateOAVB();
			break;
		}
	case OperatorLayoutType::OOB:
		{
			result = EvaluateOOB();
			break;
		}
	case OperatorLayoutType::TRUE:
		{
			result = true;
			break;
		}
	case OperatorLayoutType::UNDEFINED:
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