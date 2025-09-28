#include "Action.h"
#include "Agent.h"
#include "Room.h"
#include "OperatorManager.h"
#include "RoomManager.h"

using namespace GOAP;

std::ofstream Action::s_outFile;

Action::Action() : m_status(ExecutionStatus::INIT), m_logged(false), m_numWitness(0)
{
}

Action::~Action()
{
}

Action::operator GOAP::ActionType()
{
	return ActionType::ACTION;
}

bool Action::MightSatisfy(const Condition& cond) const
{
	for (const GOAP::Condition& effect : m_effects)//effectIter = m_effects.begin(); effectIter != m_effects.end(); ++effectIter)
	{
		if(effect == cond)
		{
			cond.CopySemantics(effect);	// Tags the semantics of the Condition as the semantics of the Action
												// This helps later for instantiating the Action clone
			return true;
		}
	}
	return false;
}

bool Action::CopyArgsFromCondition(const Condition& cond)
{
	bool result = true;
	ArgIter paramIter;
	for(int i=0; i < cond.GetNumParams(); ++i)
	{
		SemanticRole st = cond[i].semantic;
		if(st != SemanticRole::NONE)
		{
			auto arg = GetArg(st);
			
			if( arg->MatchesTypeOf(cond[i].instance) )
			{
				arg->instance = cond[i].instance;
				//arg->type = arg->instance->GetCompoundType();
			}
			else
			{
				result = false;
			}
		}
	}
	return result;
}

ArgIter Action::GetArg(SemanticRole st)
{
	ArgIter paramIter;
	for(paramIter = m_args.begin(); paramIter != m_args.end(); ++paramIter)
	{
		if((*paramIter).semantic == st)
		{
			return paramIter;
		}
	}
	return paramIter;
}

ArgIter Action::GetArg(ObjectType ot)
{
	ArgIter paramIter;
	for(paramIter = m_args.begin(); paramIter != m_args.end(); ++paramIter)
	{
		if((*paramIter).type == ot)
		{
			return paramIter;
		}
	}
	return paramIter;
}

ArgIter Action::GetArg(Object* obj)
{
	ArgIter paramIter;
	for(paramIter = m_args.begin(); paramIter != m_args.end(); ++paramIter)
	{
		if((*paramIter).instance == obj)
		{
			return paramIter;
		}
	}
	return paramIter;
}

ArgIter Action::GetFirstArg()
{
	return m_args.begin();
}

ArgIter Action::GetLastArg()
{
	return m_args.end();
}

int Action::GetPossibleInstances(Agent* agent, std::list<Action*>& result)
{
	ArgIter semanticIter;
	Argument cp;
	std::vector<Object*> unifyList;
	std::vector<std::vector<Object*> > comboList;

	for(semanticIter = m_args.begin(); semanticIter != m_args.end(); ++semanticIter)
	{
		cp = *semanticIter; 
		if(cp.instance == nullptr)
		//	for each null semantic
		{
			//	put all mathcing objects in a vector
			if(cp.semantic == SemanticRole::AGENT)
			{
				// The subject is always (for now) the agent itself
				unifyList.push_back(agent);
			}
			//else if(cp.semantic == SemanticRole::LOCATIVE)
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
			if(cp.semantic == SemanticRole::AGENT && cp.instance != agent)
			{
				// can't plan for others to do things
				return 0;
			}
			comboList.push_back(std::vector<Object*>(1, cp.instance));
		}
	}
	
	m_orderedTuples.Clear();
	m_orderedTuples.Initialize(comboList, static_cast<int>(comboList.size()));
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

	Action* action = nullptr;
	for(finalObjIter = tuples.begin(); finalObjIter != tuples.end(); ++finalObjIter)
	{
		action = GetInstanceFromTuple(*finalObjIter);
		if(action != nullptr)
		{
			result.push_back(action);
		}
	}
	//	put all vectors in a vector<vector>
	//	pass that vector to an OrderedPair
	//	append returned vector from OrderedPair to result (search frontier)
	
	return static_cast<int>(tuples.size());
}

Action* Action::GetInstanceFromTuple(std::vector<Object*>& args)
{
	Action* act = Clone();
	//act->Initialize(); // make sure arguments are initialized

	std::vector<Object*>::iterator instanceIter;
	ArgIter cpIter;

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
	ArgIter argIter;
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

void Action::CloneEffects(const Action* prototype)
{
	for (const GOAP::Condition& effect : prototype->m_effects)
	{
		m_effects.push_back(effect);
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
		return ExecutionStatus::SKIP;
	}
	else
	{
		if( EvaluatePreconditions(om) )
		{
			ExecutionStatus stat = ExecuteWorkhorse(turn);
			Dispatch(turn);

			Action::DumpToFile(turn);

			return stat;
		}
		else
		{
#ifdef _DEBUG
			std::string _str = (std::string)(*this);
			DUMP(GetArg(SemanticRole::AGENT)->instance->GetName() << " can't " << _str << ".")
			GETKEY;
#endif
			return ExecutionStatus::FAIL;
		}
	}
}

ExecutionStatus Action::GetStatus()
{
	return m_status;
}

void Action::Dispatch(int turn)
{
	auto cp = GetArg(SemanticRole::AGENT);
	this->SetLogged();
	Agent* agent = dynamic_cast<Agent*>(cp->instance);
	Room* room = agent->GetRoom();
	
	for(Agent* agent : room->GetAgents())
	{
		if(agent->IsVictim() == false)
		{
			m_numWitness++;
		}
		agent->Log(turn, this);
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

void Action::Debug()
{
}

int Action::GetNumWitness()
{
	return m_numWitness;
}

void Action::OpenFile()
{
	s_outFile.open("action_dump.txt");
}

void Action::CloseFile()
{
	s_outFile.close();
}

const std::list<Condition>& GOAP::Action::GetEffects() const
{
	return m_effects;
}

void Action::DumpToFile(int turn)
{
	s_outFile << TURN2TIME(turn) << "\t" <<Express(0, 0) << std::endl;
}

Goal* Action::FollowupGoal()
{
	return 0;
}