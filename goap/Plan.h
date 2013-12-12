#ifndef _GOAP_PLAN_H_
#define _GOAP_PLAN_H_

#include "Goal.h"
#include "IExecutable.h"

namespace GOAP
{
	namespace Op
	{
		class OperatorManager;
	}

	class Plan : public IExecutable
	{
	public:
		Plan();
		Plan(Goal* goal);
		Plan(const Plan& other);
		~Plan();

		virtual ExecutionStatus Execute(Op::OperatorManager* om, int turn) override;
		void SetPlan(Goal* goal);

		Goal* GetPlan();
		PlanStatus GetStatus();
		ExecutionStatus GetExecutionStatus();
		void SetStatus(PlanStatus status);

		Goal* Validate();

	private:
		Goal* m_plan;
		PlanStatus m_status;
	};
}

#endif