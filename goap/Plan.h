#ifndef _GOAP_PLAN_H_
#define _GOAP_PLAN_H_

#include "Goal.h"

namespace GOAP
{
	class Plan
	{
	public:
		Plan();
		Plan(Goal* goal);
		Plan(const Plan& other);
		~Plan();

		ActionStatus Execute();

	private:
		Goal* m_plan;
	};
};

#endif