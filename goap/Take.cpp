#include "Take.h"
#include "RoomManager.h"
#include "Agent.h"
#include "Prop.h"
#include "Room.h"

using namespace GOAP;

Take::Take()
{
}

Take::Take(const Take& other)
{
}

Take::~Take()
{
}

Take::operator ActionType()
{
	return ActionType::TAKE;
}

ExecutionStatus Take::ExecuteWorkhorse(int turn)
{
	auto _agent(GetArg(SemanticRole::AGENT));
	auto _patient(GetArg(SemanticRole::PATIENT));

	Prop* patient = (Prop*)_patient->instance;
	patient->SetBearer(_agent->instance);
	patient->GetRoom()->RemoveObject(patient);
	patient->SetRoom(_agent->instance->GetRoom());
	//_patient->instance->SetRoom(_agent->instance->GetRoom());
	_agent->instance->SetAttribute(AttributeType::INVENTORY, true);

	DUMP("       ** " << Express(0, 0))
	return ExecutionStatus::SUCCESS;
}

Take* Take::Clone()
{
	Take* newTake = new Take();
	newTake->CloneData(this);
	return newTake;
}


void Take::InitArgs()
{
	Argument sub, obj;

	sub.semantic = SemanticRole::AGENT;
	sub.instance = nullptr;
	sub.type = ObjectType::AGENT | ObjectType::OBJECT;
	sub.strict = true;
	m_args.push_back(sub);

	obj.semantic = SemanticRole::PATIENT;
	obj.instance = nullptr;
	obj.type = ObjectType::PROP;
	obj.strict = false;
	m_args.push_back(obj);
}

void Take::InitPreconditions()
{
	Condition subNearObj(OperatorLayoutType::OAOAB, OperatorType::EQUAL);
	Argument sub = *GetArg(SemanticRole::AGENT),
		obj = *GetArg(SemanticRole::PATIENT);

	subNearObj.GetParamByIndex(0) = sub;
	subNearObj.GetParamByIndex(0).attrib = AttributeType::ROOM;

	subNearObj.GetParamByIndex(1) = obj;
	subNearObj.GetParamByIndex(1).attrib = AttributeType::ROOM;

	m_preconds->AddCondition(subNearObj);

	/*Condition agentInventoryEmpty(OperatorLayoutType::OAVB, OperatorType::EQUAL);

	agentInventoryEmpty[0] = sub;
	agentInventoryEmpty[0].attrib = AttributeType::INVENTORY;
	agentInventoryEmpty[0].value = false;

	m_preconds->AddCondition(agentInventoryEmpty);*/
}

void Take::InitEffects()
{
	Condition subHasObj(OperatorLayoutType::OOB, OperatorType::HAS);
	Argument sub = *GetArg(SemanticRole::AGENT),
		obj = *GetArg(SemanticRole::PATIENT);

	subHasObj.GetParamByIndex(0) = sub;
	subHasObj.GetParamByIndex(1) = obj;

	m_effects.push_back(subHasObj);


	/*Condition agentInventoryFull(OperatorLayoutType::OAVB, OperatorType::EQUAL);

	agentInventoryFull[0] = sub;
	agentInventoryFull[0].attrib = AttributeType::INVENTORY;
	agentInventoryFull[0].value = true;

	m_effects.push_back(agentInventoryFull);*/

}

std::string Take::Express(Agent* agent, Room* room)
{
	auto sub = GetArg(SemanticRole::AGENT);
	auto obj = GetArg(SemanticRole::PATIENT);

	std::string _agent;
	std::string _patient;

	if(sub->instance == agent)
	{
		_agent = "I";
	}
	else
	{
		_agent = sub->instance->GetName();
	}

	if(obj->instance == agent)
	{
		_patient = "me";
	}
	else
	{
		_patient = obj->instance->GetName();
	}

	std::stringstream str;
	str << _agent << " took " << _patient;

	return str.str();
}

Take::operator std::string()
{
	return "Take";
}

float Take::Cost(RoomManager* rm)
{
	// return a measure of
	// 1 - if that thing doesn't BELONG to you
	// 2 - bonus points if it BELONGS to someone else, and not a room

	float cost;

	auto _agent = GetArg(SemanticRole::AGENT);
	auto _patient = GetArg(SemanticRole::PATIENT);
	
	if(_patient->instance->GetOwner() == 0)
	{
		cost = 10.0f;
	}
	else if(_patient->instance->GetOwner() != _agent->instance)
	{
		cost = 50.0f;
	}
	else if(_patient->instance->GetOwner() == _agent->instance)
	{
		cost = 0.0f;
	}
	
	
	return cost;
}

void Take::UpdateConditionInstances()
{
	Action::UpdateConditionInstances();
}

void Take::Dispatch(int turn)
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
		if( agent != GetArg(SemanticRole::AGENT)->instance ) // Treat murdere differently
		{
			agent->Log(turn, this);
		}
	}
	
	switch(m_numWitness)
	{
	case 1:
		// YOU WHERE ALONE
		// LIE ABOUT WHERE YOU WERE
		
		break;
	case 2:
		{
			// SOMEONE SAW YOU
			// PIN IT ON THEM
			Take* take = (Take*)this->Clone();
			for(Agent* agent : room->GetAgents())
			{
				if(!agent->IsVictim() && agent != GetArg(SemanticRole::AGENT)->instance )
				{
					take->GetArg(SemanticRole::AGENT)->instance = agent;
				}
			}
			Agent* falseAgent = (Agent*)cp->instance;
			falseAgent->Log(turn, take);
			break;
		}
	default:
		// MORE THAN ONE PERSON SAW YOU
		// THIS IS NOT A GOOD SCENARIO
		break;
	};
}