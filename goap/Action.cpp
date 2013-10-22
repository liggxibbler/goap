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

void Action::CopyArgsFromCondition(Condition& cond)
{
	std::list<ConditionParameter>::iterator paramIter;
	for(int i=0; i < cond.GetNumParams(); ++i)
	{
		(*(GetArgByType(cond[i].type))).instance = cond[i].instance;
	}
}

std::list<ConditionParameter>::iterator Action::GetArgBySemantic(OperandSemanticType st)
{
	std::list<ConditionParameter>::iterator paramIter;
	for(paramIter = m_args.begin(); paramIter != m_args.end(); ++paramIter)
	{
		if((*paramIter).semantic = st)
		{
			return paramIter;
		}
	}
	return paramIter;
}

std::list<ConditionParameter>::iterator Action::GetArgByType(ObjectType ot)
{
	std::list<ConditionParameter>::iterator paramIter;
	for(paramIter = m_args.begin(); paramIter != m_args.end(); ++paramIter)
	{
		if((*paramIter).type = ot)
		{
			return paramIter;
		}
	}
	return paramIter;
}

std::list<ConditionParameter>::iterator Action::GetArgByInstance(Object* obj)
{
	std::list<ConditionParameter>::iterator paramIter;
	for(paramIter = m_args.begin(); paramIter != m_args.end(); ++paramIter)
	{
		if((*paramIter).instance = obj)
		{
			return paramIter;
		}
	}
	return paramIter;
}