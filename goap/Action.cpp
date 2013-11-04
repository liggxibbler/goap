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
	CondIter effectIter;
	for(effectIter = m_effects.begin(); effectIter != m_effects.end(); ++effectIter)
	{
		if(*effectIter == cond)
		{
			cond.CopySemantics(*effectIter);	// Tags the semantics of the Condition as the semantics of the Action
												// This helps later for instantiating the Action clone
			return true;
		}
	}
	return false;
}

void Action::CopyArgsFromCondition(Condition& cond)
{
	CondParamIter paramIter;
	for(int i=0; i < cond.GetNumParams(); ++i)
	{
		OperandSemanticType st = cond[i].semantic;
		if(st != OP_SEMANTIC_TYPE_NONE)
		{
			(*(	GetArgBySemantic(st))).instance = cond[i].instance;
			cond[i].semantic = OP_SEMANTIC_TYPE_NONE; // reset for later checks
		}
	}
}

CondParamIter Action::GetArgBySemantic(OperandSemanticType st)
{
	CondParamIter paramIter;
	for(paramIter = m_args.begin(); paramIter != m_args.end(); ++paramIter)
	{
		if((*paramIter).semantic == st)
		{
			return paramIter;
		}
	}
	return paramIter;
}

CondParamIter Action::GetArgByType(ObjectType ot)
{
	CondParamIter paramIter;
	for(paramIter = m_args.begin(); paramIter != m_args.end(); ++paramIter)
	{
		if((*paramIter).type == ot)
		{
			return paramIter;
		}
	}
	return paramIter;
}

CondParamIter Action::GetArgByInstance(Object* obj)
{
	CondParamIter paramIter;
	for(paramIter = m_args.begin(); paramIter != m_args.end(); ++paramIter)
	{
		if((*paramIter).instance == obj)
		{
			return paramIter;
		}
	}
	return paramIter;
}

CondParamIter Action::GetFirstArg()
{
	return m_args.begin();
}

CondParamIter Action::GetLastArg()
{
	return m_args.end();
}

bool Action::GetPossibleInstances(Agent* agent, std::list<Action*>& result)
{
	CondParamIter semanticIter;
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
		tuples.push_back(m_orderedTuples.GetNextOrderedPair(stat));
	}

	std::vector<std::vector<Object*> >::iterator finalObjIter;

	for(finalObjIter = tuples.begin(); finalObjIter != tuples.end(); ++finalObjIter)
	{
		result.push_back(GetInstanceFromTuple(*finalObjIter));
	}
	//	put all vectors in a vector<vector>
	//	pass that vector to an OrderedPair
	//	append returned vector from OrderedPair to result (search frontier)
	
	return true;
}

Action* Action::GetInstanceFromTuple(std::vector<Object*> args)
{
	Action* act = Clone();
	act->Initialize(); // make sure arguments are initialized

	std::vector<Object*>::iterator instanceIter;
	CondParamIter cpIter;

	cpIter = m_args.begin();
	instanceIter = args.begin();

	for(unsigned int i=0; i<m_args.size(); ++i)
	{
		(*cpIter++).instance = (*instanceIter++);
	}

	return act;
}

Goal* Action::GetGoal()
{
	return m_preconds;
}

void Action::Initialize()
{
	m_preconds = new Goal;
	InitArgs();
	InitPreconditions();
	InitEffects();
}

void Action::CloneArgs(Action* prototype)
{
	CondParamIter argIter;
	for(argIter = prototype->GetFirstArg(); argIter != prototype->GetLastArg(); ++argIter)
	{
		m_args.push_back(*argIter);
	}
}

void Action::ClonePreconds(Action* prototype)
{
	CondIter condIter;
	for(condIter = prototype->GetPreconds()->GetFirstCondition();
		condIter != prototype->GetPreconds()->GetLastCondition();
		++condIter)
	{
		m_preconds->AddCondition(*condIter);
	}
}

void Action::CloneEffects(Action* prototype)
{
	CondIter condIter;
	for(condIter = prototype->GetFirstEffect(); condIter != prototype->GetLastEffect(); ++condIter)
	{
		m_effects.push_back(*condIter);
	}
}

Goal* Action::GetPreconds()
{
	return m_preconds;
}

void Action::CloneData(Action* prototype)
{
	m_preconds = new Goal();
	CloneArgs(prototype);
	CloneEffects(prototype);
	ClonePreconds(prototype);
}

CondIter Action::GetFirstEffect()
{
	return m_effects.begin();
}

CondIter Action::GetLastEffect()
{
	return m_effects.end();
}