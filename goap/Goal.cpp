#include "Goal.h"

using namespace GOAP;

Goal::Goal()
{
	m_action = NULL;
	m_parent = NULL;
	m_depth = 0;
	m_cost = 0;
	m_negate = false;
}

Goal::Goal(Goal* parent, Action* action, bool negate) :
m_parent(parent), m_action(action), m_negate(negate)
{
}

Goal::Goal(const Goal& other)
{
}

Goal::~Goal()
{
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
			break;
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

void Goal::AddCondition(Condition cond)
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