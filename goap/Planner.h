#ifndef _GOAP_PLANNER_H_
#define _GOAP_PLANNER_H_

#include "Object.h"
#include "Agent.h"
#include "Action.h"
#include <list>

namespace GOAP
{
	class Planner
	{
	public:
		Action** Plan();
	};
}

#endif