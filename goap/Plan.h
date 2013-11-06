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
		void SetPlan(Goal* goal);

		Goal* GetPlan();
		PlanStatus GetStatus();
		void SetStatus(PlanStatus status);

	private:
		Goal* m_plan;
		PlanStatus m_status;
	};
}

#endif