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

GOAP::ActionType Action::GetActionType() const
{
	return ActionType::ACTION;
}

std::optional<const Condition*> Action::GetCompatibleEffect(const Condition* cond) const
{
	for (const GOAP::Condition& effect : m_effects)
	{
		if(effect == *cond)
		{
			return &effect;
		}
	}
	return std::optional<const Condition*>{};
}

bool Action::CopyArgInstancesFromCondition(const Condition& cond)
{
	bool result = true;
	for(int i=0; i < cond.GetNumParams(); ++i)
		// for each parameter in the condition
	{
		SemanticRole conditionParameterSemantic = cond[i].semantic;
		
		if (conditionParameterSemantic == SemanticRole::NONE)
			// if the parameter has no semantic, skip it
			continue;

		// get the argument from the action with the same semantic
		Argument& actionArgumentBySemantic = GetArg(conditionParameterSemantic);
			
		// if the action's arguments and the condition's parameter's instance have compatible types
		if( actionArgumentBySemantic.MatchesTypeOf(cond[i].instance) )
		{
			// copy the parameter's instance to the action's argument
			actionArgumentBySemantic.instance = cond[i].instance;
			//arg->type = arg->instance->GetCompoundType();
		}
		else
		{
			// otherwise, there is a mismatch between the action and the condition
			result = false;
		}		
	}
	return result;
}

Argument& Action::GetArg(SemanticRole st)
{
	for (Argument& arg : m_args)
	{
		if(arg.semantic == st)
		{
			return arg;
		}
	}

	throw;
}

Argument& Action::GetArg(ObjectType ot)
{
	for(Argument& arg : m_args)
	{
		if(arg.type == ot)
		{
			return arg;
		}
	}

	throw;
}

Argument& Action::GetArg(Object* obj)
{
	for (Argument& arg : m_args)
	{
		if(arg.instance == obj)
		{
			return arg;
		}
	}

	throw;
}

const Argument& Action::GetArg(SemanticRole st) const
{
	for (const Argument& arg : m_args)
	{
		if (arg.semantic == st)
		{
			return arg;
		}
	}

	throw;
}

const Argument& Action::GetArg(ObjectType ot) const
{
	for (const Argument& arg : m_args)
	{
		if (arg.type == ot)
		{
			return arg;
		}
	}

	throw;
}

const Argument& Action::GetArg(Object* obj) const
{
	for (const Argument& arg : m_args)
	{
		if (arg.instance == obj)
		{
			return arg;
		}
	}

	throw;
}


int Action::GetPossibleInstances(Agent* agent, std::list<Action*>& result)
{
	std::vector<Object*> unifyList;
	std::vector<std::vector<Object*> > comboList;

	for(Argument& argument : m_args)
	{
		if(argument.instance == nullptr)
		//	for each null semantic
		{
			//	put all mathcing objects in a vector
			if(argument.semantic == SemanticRole::AGENT)
			{
				// The subject is always (for now) the agent itself
				unifyList.push_back(agent);
			}
			else if(!agent->Unify(argument.type, unifyList, argument.strict))
			{
				//	if vector is empty : unification not possible
				return 0;
			}
			comboList.push_back(unifyList);
			unifyList.clear();
		}
		else
		{
			if(argument.semantic == SemanticRole::AGENT && argument.instance != agent)
			{
				// can't plan for others to do things
				return 0;
			}
			comboList.push_back(std::vector<Object*>(1, argument.instance));
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
	std::list<Argument>::iterator cpIter;

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
	for(Argument& arg : prototype->m_args)
	{
		m_args.push_back(arg);
	}
}

void Action::ClonePreconds(Action* prototype)
{
	for(const Condition& condition : prototype->GetPreconds()->GetConditions())
	{
		m_preconds->AddCondition(condition);
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
	for (Condition& effect : m_effects)
	{
		for(int i = 0; i < effect.GetNumParams(); ++i)
		{
			SemanticRole st = effect.GetParamByIndex(i).semantic;
			effect.GetParamByIndex(i).instance	= GetArg(st).instance;
		}
	}
}

void Action::UpdatePrecondInstances()
{
	for (Condition& precond : m_preconds->GetConditions())
	{
		for(int i = 0; i < precond.GetNumParams(); ++i)
		{
			SemanticRole st = precond.GetParamByIndex(i).semantic;
			precond.GetParamByIndex(i).instance = GetArg(st).instance;
		}
	}
}

ExecutionStatus Action::Execute(const Op::OperatorManager& om, int turn)
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
			std::string _str = GetName();
			DUMP(GetArg(SemanticRole::AGENT).instance->GetName() << " can't " << _str << ".")
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
	const Argument& cp = GetArg(SemanticRole::AGENT);
	this->SetLogged();
	Agent* agent = dynamic_cast<Agent*>(cp.instance);
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

bool Action::EvaluatePreconditions(const Op::OperatorManager& om)
{
	return m_preconds->Evaluate(om);
}

bool Action::EvaluateEffects(const Op::OperatorManager& om)
{
	for(const Condition& effect : m_effects)
	{
		if( ! effect.Evaluate(om) )
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
	s_outFile << TURN2TIME(turn) << "\t" <<Express(nullptr, nullptr) << std::endl;
}

Goal* Action::FollowupGoal()
{
	return nullptr;
}