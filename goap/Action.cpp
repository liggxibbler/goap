#include "Action.h"
#include "Agent.h"
#include "Room.h"
#include "OperatorManager.h"
#include "RoomManager.h"

using namespace GOAP;

Action::Action() : m_status(EXEC_STAT_INIT), m_logged(false)
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

bool Action::CopyArgsFromCondition(Condition& cond)
{
	bool result = true;
	CondParamIter paramIter;
	for(int i=0; i < cond.GetNumParams(); ++i)
	{
		SemanticRole st = cond[i].semantic;
		if(st != SEMANTIC_ROLE_NONE)
		{
			auto arg = GetArg(st);
			
			if( arg->MatchesTypeOf(cond[i].instance) )
			{
				arg->instance = cond[i].instance;
			}
			else
			{
				result = false;
			}

			cond[i].semantic = SEMANTIC_ROLE_NONE; // reset for later checks
		}
	}
	return result;
}

CondParamIter Action::GetArg(SemanticRole st)
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

CondParamIter Action::GetArg(ObjectType ot)
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

CondParamIter Action::GetArg(Object* obj)
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

int Action::GetPossibleInstances(Agent* agent, std::list<Action*>& result)
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
			//	put all mathcing objects in a vector
			if(cp.semantic == SEMANTIC_ROLE_AGENT)
			{
				// The subject is always (for now) the agent itself
				unifyList.push_back(agent);
			}
			//else if(cp.semantic == SEMANTIC_ROLE_LOCATIVE)
			//{
			//	// push all rooms on unifyList
			//	DUMP("")
			//}
			else if(!agent->Unify(cp.type, unifyList, cp.strict))
			{
				//	if vector is empty : unification not possible
				return 0;
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
		std::vector<Object*> vecObj = m_orderedTuples.GetNextOrderedPair(stat);
		if(!stat)
		{
			tuples.push_back(vecObj);
		}
	}

	std::vector<std::vector<Object*> >::iterator finalObjIter;

	Action* action = NULL;
	for(finalObjIter = tuples.begin(); finalObjIter != tuples.end(); ++finalObjIter)
	{
		action = GetInstanceFromTuple(*finalObjIter);
		if(action != 0)
		{
			result.push_back(action);
		}
	}
	//	put all vectors in a vector<vector>
	//	pass that vector to an OrderedPair
	//	append returned vector from OrderedPair to result (search frontier)
	
	return tuples.size();
}

Action* Action::GetInstanceFromTuple(std::vector<Object*>& args)
{
	Action* act = Clone();
	//act->Initialize(); // make sure arguments are initialized

	std::vector<Object*>::iterator instanceIter;
	CondParamIter cpIter;

	cpIter = act->m_args.begin();
	instanceIter = args.begin();

	for(unsigned int i=0; i<m_args.size(); ++i)
	{
		cpIter->instance = *(instanceIter++);
		++cpIter;
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

void Action::UpdateConditionInstances()
{
	UpdateEffectInstances();
	UpdatePrecondInstances();
}

void Action::UpdateEffectInstances()
{
	CondIter effect;
	for (effect = m_effects.begin(); effect != m_effects.end(); ++effect)
	{
		for(int i = 0; i < effect->GetNumParams(); ++i)
		{
			SemanticRole st = effect->GetParamByIndex(i).semantic;
			effect->GetParamByIndex(i).instance	= GetArg(st)->instance;
		}
	}
}

void Action::UpdatePrecondInstances()
{
	CondIter precond;
	for (precond = m_preconds->GetFirstCondition(); precond != m_preconds->GetLastCondition(); ++precond)
	{
		for(int i = 0; i < precond->GetNumParams(); ++i)
		{
			SemanticRole st = precond->GetParamByIndex(i).semantic;
			precond->GetParamByIndex(i).instance = GetArg(st)->instance;
		}
	}
}

ExecutionStatus Action::Execute(Op::OperatorManager* om, int turn)
{
	// log action to local database
	// send message to all agents in room
	if( EvaluateEffects(om) )
	{
		return EXEC_STAT_SKIP;
	}
	else
	{
		if( EvaluatePreconditions(om) )
		{
			Dispatch(turn);
			ExecutionStatus stat = ExecuteWorkhorse(turn);
			this->SetLogged();
			return stat;
		}
		else
		{
#ifdef _GOAP_DEBUG
			std::string _str = (std::string)(*this);
			DUMP("Can't " << _str << ".")
			std::cin.get();
#endif
			return EXEC_STAT_FAIL;
		}
	}
}

ExecutionStatus Action::GetStatus()
{
	return m_status;
}

void Action::Dispatch(int turn)
{
	auto cp = GetArg(SEMANTIC_ROLE_AGENT);
	Agent* agent = dynamic_cast<Agent*>(cp->instance);
	Room* room = agent->GetRoom();
	for(auto agent(room->GetFirstAgent());agent != room->GetLastAgent();++agent)
	{
		(*agent)->Log(turn, this);
	}
}

bool Action::CompareCost(Action* a1, Action* a2)
{
	RoomManager* rm = RoomManager::Instance();
	return ( a1->Cost(rm) < a2->Cost(rm) );
}

bool Action::EvaluatePreconditions(Op::OperatorManager* om)
{
	return m_preconds->Evaluate(om);
}

bool Action::EvaluateEffects(Op::OperatorManager* om)
{
	for(auto effect(m_effects.begin()); effect!= m_effects.end(); ++effect)
	{
		if( ! effect->Evaluate(om) )
		{
			return false;
		}
	}
	return true;
}

bool Action::IsLogged()
{
	return m_logged;
}
void Action::SetLogged()
{
	m_logged = true;
}