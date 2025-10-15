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

bool Operator::Evaluate(const Condition& ac) const
{
	bool result;
	
	const Argument* params = ac.GetNumParams() != 0 ? ac.GetParams() : nullptr;
	bool negate = ac.GetNegate();

	switch(ac.GetOperatorLayoutType())
	{
	case OperatorLayoutType::OAOAB:
		{
		result = EvaluateOAOAB(params);
			break;
		}
	case OperatorLayoutType::OAVB:
		{
		result = EvaluateOAVB(params);
			break;
		}
	case OperatorLayoutType::OOB:
		{
		result = EvaluateOOB(params);
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
	
	if(negate)
		result = !result;

	return result;
}