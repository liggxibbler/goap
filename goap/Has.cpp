#include "Has.h"

#include "Prop.h"

using namespace GOAP;
using namespace GOAP::Op;

bool Has::EvaluateOOB (const Argument* params) const
{
	const Prop* objProp = dynamic_cast<Prop*>(params[1].instance);
	return objProp->GetBearer() == params[0].instance;
}

bool Has::EvaluateOAVB (const Argument* params) const
{
	return false;
}

bool Has::EvaluateOAOAB (const Argument* params) const
{
	return false;
}
