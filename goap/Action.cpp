#include "Action.h"
#include "Agent.h"

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

bool Action::MightSatisfy(Condition& cond)
{
	std::list<Condition>::iterator effectIter;
	for(effectIter = m_effects.begin(); effectIter != m_effects.end(); ++effectIter)
	{
		if(*effectIter == cond)
		{
			return true;
		}
	}
	return false;
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

std::list<ConditionParameter>::iterator Action::GetFirstArg()
{
	return m_args.begin();
}

std::list<ConditionParameter>::iterator Action::GetLastArg()
{
	return m_args.end();
}

bool Action::GetPossibleInstances(Agent* agent, std::list<Action*>& result)
{
	std::list<ConditionParameter>::iterator semanticIter;
	ConditionParameter cp;
	std::vector<Object*> unifyList;
	std::vector<std::vector<Object*> > comboList;

	for(semanticIter = m_args.begin(); semanticIter != m_args.end(); ++semanticIter)
	{
		cp = *semanticIter; 
		if(cp.instance == NULL)
		//	for each null semantic
		{
			//	put all mathing objects in a vector
			if(!agent->Unify(cp.type, unifyList))
			{
				//	if vector is empty : unification not possible
				return false;
			}
			comboList.push_back(unifyList);
			unifyList.clear();
		}
		else
		{
			comboList.push_back(std::vector<Object*>(1, cp.instance));
		}
	}
	
	m_orderedTuples.Clear();
	m_orderedTuples.Initialize(comboList, comboList.size());
	std::vector<std::vector<Object*> > tuples;

	for (bool stat = false; stat == false;)
	{
		tuples.push_back(m_orderedTuples.GetNextCombination(stat));
	}



	//	put all vectors in a vector<vector>
	//	pass that vector to a combination
	//	append returned vector from combination to result (search frontier)
	
	return true;
}