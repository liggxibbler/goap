#include "Operator.h"

using namespace GOAP;

Operator::Operator()
{}

Operator::Operator(const Operator& other)
{}

Operator::~Operator()
{}

// might make non-pure virtual, for exception handling...

bool Operator::Evaluate(ConcreteCondition cc)
{
	bool result;
	m_attribs = cc.GetAttributes();
	m_objectPtrs = cc.GetObjects();
	m_values = cc.GetValues();
	m_negate = cc.GetNegate();

	switch(cc.GetOperatorLayoutType())
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
	case OP_LAYOUT_TYPE_OOAB:
		{
			result = EvaluateOOAB();
			break;
		}
	case OP_LAYOUT_TYPE_OOB:
		{
			result = EvaluateOOB();
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
	return result;
}