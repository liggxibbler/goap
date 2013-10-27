#include "Goal.h"

using namespace GOAP;

Goal::Goal()
{
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

	std::list<Condition>::iterator condIter;

	for(condIter = m_conditions.begin(); condIter != m_conditions.end(); ++condIter)
	{
		if ( (*condIter).Evaluate(om) )
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