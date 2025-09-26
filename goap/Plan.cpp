#include "Plan.h"
#include "Action.h"

using namespace GOAP;

Plan::Plan()
{
	m_plan = nullptr;
	m_lastPlan = nullptr;
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
	
	if(action != nullptr)
	{
		ExecutionStatus stat = action->Execute(om, turn);
		m_execStat = stat;
		switch(stat)
		{
		case ExecutionStatus::SUCCESS:
		case ExecutionStatus::MURDER:
			// delete this one
			m_lastPlan = m_plan;
			m_plan = m_plan->GetParent();
			// and no replanning is needed
			m_execStat = ExecutionStatus::RUNNING;
			break;
		case ExecutionStatus::SKIP:
			m_plan = m_plan->GetParent();
			m_execStat = this->Execute(om, turn);
			break;
		case ExecutionStatus::RUNNING:
			//
			//m_plan = m_plan;
			// and no replanning is needed
			break;
		case ExecutionStatus::FAIL:
			// delete this one
			//m_plan = m_plan->GetParent();
			// but replanning is needed
			break;
		default:
			// throw exception
			m_execStat = ExecutionStatus::UNKNOWN;
			break;
		};
		return m_execStat;
	}
	else
	{
		// this is the ultimate goal
		//
		m_execStat = ExecutionStatus::DONE;
		return m_execStat;
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
	return m_execStat;
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

			for(const Condition& effect : temp->GetAction()->GetEffects())
			{
				temp->RemoveCondition(effect);
			}

			temp->SetAction( temp->GetParent()->GetAction() );
			temp->SetParent( temp->GetParent()->GetParent() );
		}

		temp->SetAction( m_plan->GetAction());
		temp->SetParent( m_plan->GetParent());

		while(temp->GetParent() != 0)
		{
			for (const Condition& effect : temp->GetAction()->GetEffects())
			{
				temp->RemoveCondition(effect);
			}

			temp->SetAction( temp->GetParent()->GetAction() );
			temp->SetParent( temp->GetParent()->GetParent() );
		}

		//// Only True conditions should be left
		int numTrue = 0;
		for(auto condition(temp->GetFirstCondition()); condition != temp->GetLastCondition() ; ++condition)
		{
		//	if ( condition->GetOperatorType() == OperatorType::TRUE )
		//	{
		//		numTrue++;
		//	}

			if( condition->Evaluate(Op::OperatorManager::Instance()) )
			{
				numTrue++;
			}
		}
		
		if (temp->GetNumConditions() == numTrue)
		{
//			delete temp;
			temp = 0;
			return m_plan;
		}
		else
		{
			//Goal::~Goal is not written correctly, redo!
			//delete temp;
			temp = 0;
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

Goal* Plan::FollowupGoal()
{
	return m_lastPlan->GetAction()->FollowupGoal();
}

void Plan::Pause()
{
	m_ExecStatStored = m_execStat;
	m_execStat = ExecutionStatus::PAUSED;
}

void Plan::Resume()
{
	m_execStat = m_ExecStatStored;
}