#ifndef _GOAP_PLAN_H_
#define _GOAP_PLAN_H_

#include "Goal.h"
#include "IExecutable.h"

namespace GOAP
{
	class Plan : public IExecutable
	{
	public:
		Plan();
		Plan(Goal* goal);
		Plan(const Plan& other);
		~Plan();

		virtual ActionStatus Execute() override;
		void SetPlan(Goal* goal);

		Goal* GetPlan();
		PlanStatus GetStatus();
		ActionStatus GetActionStatus();
		void SetStatus(PlanStatus status);

	private:
		Goal* m_plan;
		PlanStatus m_status;
	};
}

#endif