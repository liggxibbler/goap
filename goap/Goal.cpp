#include "Goal.h"
#include "Action.h"
#include "Plan.h"

using namespace GOAP;

Goal::Goal()
{
	m_action = NULL;
	m_parent = NULL;
	m_depth = 0;
	m_cost = 0;
	m_plan = new Plan();
	m_plan->SetStatus(PLAN_STAT_UNKNOWN);
	m_negate = false;
}

Goal::Goal(Goal* parent, Action* action, bool negate) :
m_parent(parent), m_action(action), m_negate(negate)
{
	m_depth = 0;
	m_cost = 0;
	m_plan = new Plan();
	m_plan->SetStatus(PLAN_STAT_UNKNOWN);
}

//Goal::Goal(const Goal& other)
//{
//	m_parent = other.m_parent;
//	m_action = other.m_action;
//	m_negate = other.m_negate;
//	m_depth = other.m_depth;
//	m_cost = other.m_cost;
//	
//	for(auto cond(other.m_conditions.begin()); cond != other.m_conditions.end(); ++cond)
//	{
//		m_conditions.push_back(*cond);
//	}
//}

Goal::~Goal()
{
	// IS THIS NECESSARY?
	//if(m_action != 0)
	//{
	//	if(m_action->IsLogged() == false)
	//	{
	//		delete m_action;
	//		m_action = 0;
	//	}
	//}
	for(auto child(m_children.begin()); child != m_children.end(); ++child)
	{
		delete (*child);
	}
}

bool Goal::Evaluate(Op::OperatorManager* om)
{
	bool result = true;

	CondIter condIter;

	for(condIter = m_conditions.begin(); condIter != m_conditions.end(); ++condIter)
	{
		Condition cond = *condIter;
		if ( !cond.Evaluate(om) )
		{
			result = false;
			//break;
		}
		else
		{
			//m_conditions.erase(condIter);
		}
	}

	if ( m_negate )
	{
		result = !result;
	}

	return result;
}

bool Goal::IsConsistent(Op::OperatorManager* om)
{
	return false;
}

void Goal::AddChild(Goal* child)
{
	m_children.push_back(child);
}

Goal* Goal::GetParent()
{
	return m_parent;
}

std::list<Goal*>::iterator Goal::GetFirstChild()
{
	return m_children.begin();
}

void Goal::AddCondition(Condition& cond)
{
	m_conditions.push_back(cond);
}

CondIter Goal::GetFirstCondition()
{
	return m_conditions.begin();
}
CondIter Goal::GetLastCondition()
{
	return m_conditions.end();
}

int Goal::GetDepth()
{
	return m_depth;
}

Goal* Goal::Combine(Goal* other)
{
	return NULL;
}

Goal* Goal::Clone()
{
	Goal* clone = new Goal();
	
	std::list<Condition>::iterator condIter;
	for(condIter = m_conditions.begin(); condIter != m_conditions.end(); ++condIter)
	{
		clone->AddCondition(*condIter);
	}
	
	clone->m_negate = m_negate;
	clone->m_depth = m_depth;
	clone->m_cost = m_cost;
	
	return clone;
}

void Goal::RemoveCondition(Condition& cond)
{
	// From stackoverflow.com
	// http://stackoverflow.com/users/46821/michael-kristofik

	CondIter rem = m_conditions.begin();
	
	while(rem != m_conditions.end())
	{
		if(rem->EqualInstance(cond))
		{
			m_conditions.erase(rem++);
		}
		else
		{
			++rem;
		}
	}
}

void Goal::SetAction(Action* action)
{
	m_action = action;
}

void Goal::SetParent(Goal* parent)
{
	m_parent = parent;
}

Action* Goal::GetAction()
{
	return m_action;
}

void Goal::ClearChildren()
{
	auto child(m_children.begin());
	while(child != m_children.end())
	{
		delete (*child);
		m_children.erase(child++);
	}
}

int Goal::GetNumConditions()
{
	return m_conditions.size();
}

void Goal::SetCost(int cost)
{
	m_cost = cost;
}

int Goal::GetCost()
{
	return m_cost;
}

void Goal::SetDepth(int depth)
{
	m_depth = depth;
}

Plan* Goal::GetPlan()
{
	return m_plan;
}

void Goal::SetPriority(int priority)
{
	m_priority = priority;
}

int Goal::GetPriority()
{
	return m_priority;
}