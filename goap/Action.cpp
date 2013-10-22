#include "Action.h"

using namespace GOAP;

Action::Action()
{
}

Action::~Action()
{
}

Action::operator GOAP::ActionType()
{
	return ACTION_ACTION;
}

Condition* Action::operator == (Condition& cond)
{
	std::list<Condition>::iterator effectIter;
	for(effectIter = m_effects.begin(); effectIter != m_effects.end(); ++effectIter)
	{
		if(*effectIter == cond)
		{
			return &(*effectIter);
		}
	}
	return NULL;
}

void Action::CopySemanticsFromCondition(Condition& cond)
{
	std::map<OperandSemanticType, Object*>::iterator semanticIter;
	for(semanticIter = m_args.begin(); semanticIter != m_args.end(); ++semanticIter)
	{
		//for param in cond
		//	m_args.getParamByType(param.type).instance = param.instance
		//
		//
		//
		//
	}
}