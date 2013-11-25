#include "Plan.h"
#include "Action.h"

using namespace GOAP;

Plan::Plan()
{
	m_plan = NULL;
}

Plan::Plan(Goal* goal) : m_plan(goal)
{
}

Plan::Plan(const Plan& other)
{
	m_plan = other.m_plan;
}

Plan::~Plan()
{
}

ActionStatus Plan::Execute()
{
	Action* action = m_plan->GetAction();
	
	if(action != NULL)
	{
		switch(action->Execute())
		{
		case ACT_STAT_SUCCESS:
			// delete this one
			m_plan = m_plan->GetParent();
			// and no replanning is needed
			return ACT_STAT_SUCCESS;
		case ACT_STAT_RUNNING:
			//
			//m_plan = m_plan;
			// and no replanning is needed
			return ACT_STAT_RUNNING;
		case ACT_STAT_FAIL:
			// delete this one
			m_plan = m_plan->GetParent();
			// but replanning is needed
			return ACT_STAT_FAIL;
		default:
			// throw exception
			return ACT_STAT_UNKNOWN;
			break;
		};
	}
	else
	{
		// this is the ultimate goal
		// 
		return ACT_STAT_DONE;
	}
}

void Plan::SetPlan(Goal* goal)
{
	m_plan = goal;
}

Goal* Plan::GetPlan()
{
	return m_plan;
}

PlanStatus Plan::GetStatus()
{
	return m_status;
}

void Plan::SetStatus(PlanStatus status)
{
	m_status = status;
}