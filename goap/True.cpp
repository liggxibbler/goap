#include "True.h"

using namespace GOAP;
using namespace GOAP::Op;

bool True::EvaluateOAVB ()
{
	return true;
}
bool True::EvaluateOAOAB ()
{
	return true;
}
bool True::EvaluateOOB ()
{
	return true;
}