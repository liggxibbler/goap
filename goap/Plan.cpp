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
	delete m_plan;
}

ExecutionStatus Plan::Execute(Op::OperatorManager* om, int turn)
{
	Action* action = m_plan->GetAction();
	
	if(action != NULL)
	{
		ExecutionStatus stat = action->Execute(om, turn);
		switch(stat)
		{
		case EXEC_STAT_SUCCESS:
		case EXEC_STAT_MURDER:
			// delete this one
			m_plan = m_plan->GetParent();
			// and no replanning is needed
			return EXEC_STAT_RUNNING;
		case EXEC_STAT_SKIP:
			m_plan = m_plan->GetParent();
			return this->Execute(om, turn);
		case EXEC_STAT_RUNNING:
			//
			//m_plan = m_plan;
			// and no replanning is needed
			break;
		case EXEC_STAT_FAIL:
			// delete this one
			//m_plan = m_plan->GetParent();
			// but replanning is needed
			break;
		default:
			// throw exception
			return EXEC_STAT_UNKNOWN;
			break;
		};
		return stat;
	}
	else
	{
		// this is the ultimate goal
		// 
		return EXEC_STAT_DONE;
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

ExecutionStatus Plan::GetExecutionStatus()
{
	return m_plan->GetAction()->GetStatus();
}

Goal* Plan::Validate()
{
	// Make sure this plan will satisfy every precondition of every action when executed
	if(m_plan != 0)
	{
		Goal* temp = new Goal(*m_plan);

		// Pool all preconditions
		while(temp->GetParent() != 0)
		{
			// temp.conds += temp.parent.conds
			for(auto cond(temp->GetParent()->GetFirstCondition());
				cond != temp->GetParent()->GetLastCondition() ; ++cond)
			{
				temp->AddCondition(*cond);
			}

			for(auto effect(temp->GetAction()->GetFirstEffect());
				effect != temp->GetAction()->GetLastEffect() ; ++effect)
			{
				temp->RemoveCondition(*effect);
			}

			temp->SetAction( temp->GetParent()->GetAction() );
			temp->SetParent( temp->GetParent()->GetParent() );
		}

		temp->SetAction( m_plan->GetAction());
		temp->SetParent( m_plan->GetParent());

		while(temp->GetParent() != 0)
		{
			for(auto effect(temp->GetAction()->GetFirstEffect());
				effect != temp->GetAction()->GetLastEffect() ; ++effect)
			{
				temp->RemoveCondition(*effect);
			}

			temp->SetAction( temp->GetParent()->GetAction() );
			temp->SetParent( temp->GetParent()->GetParent() );
		}

		//// Only True conditions should be left
		//int numTrue = 0;
		//for(auto condition(temp->GetFirstCondition()); condition != temp->GetLastCondition() ; ++condition)
		//{
		//	if ( condition->GetOperatorType() == OPERATOR_TRUE )
		//	{
		//		numTrue++;
		//	}

		//	if( condition->Evaluate(Op::OperatorManager::Instance()) )
		//	{
		//		numTrue++;
		//	}
		//}
		
		if (temp->GetNumConditions() == 0)
		{
			delete temp;
			temp = 0;
			return m_plan;
		}
		else
		{
			delete temp;
			temp = 0;
			return 0;
		}
	}
	else
	{
		return 0;
	}
}