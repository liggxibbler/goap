#include "Drop.h"
#include "RoomManager.h"
#include "Room.h"
#include "Agent.h"

using namespace GOAP;

Drop::Drop()
{
}

Drop::Drop(const Drop& other)
{
}

Drop::~Drop()
{
}

Drop::operator ActionType()
{
	return ActionType::DROP;
}

ExecutionStatus Drop::ExecuteWorkhorse(int turn)
{
	auto _agent(GetArg(SemanticRole::AGENT));
	auto _patient(GetArg(SemanticRole::PATIENT));

	Prop* patient = (Prop*)_patient->instance;
	patient->SetBearer(0);
	_agent->instance->GetRoom()->AddObject(patient);
	_agent->instance->SetAttribute(AttributeType::INVENTORY, false);

	DUMP("       ** " << Express(0, 0))
	return ExecutionStatus::SUCCESS;
}

Drop* Drop::Clone()
{
	Drop* newDrop = new Drop();
	newDrop->CloneData(this);
	return newDrop;
}


void Drop::InitArgs()
{
	Argument agent, patient, locative;

	agent.semantic = SemanticRole::AGENT;
	agent.instance = nullptr;
	agent.type = ObjectType::AGENT | ObjectType::OBJECT;
	agent.strict = true;
	m_args.push_back(agent);

	patient.semantic = SemanticRole::PATIENT;
	patient.instance = nullptr;
	patient.type = ObjectType::PROP;
	patient.strict = false;
	m_args.push_back(patient);

	locative.semantic = SemanticRole::LOCATIVE;
	locative.instance = nullptr;
	locative.type = ObjectType::ROOM | ObjectType::OBJECT;
	locative.strict = true;
	m_args.push_back(locative);
}

void Drop::InitPreconditions()
{
	Argument agent = *GetArg(SemanticRole::AGENT),
		patient = *GetArg(SemanticRole::PATIENT),
		locative = *GetArg(SemanticRole::LOCATIVE);

	Condition agentHasPatient(OperatorLayoutType::OOB, OperatorType::HAS);

	agentHasPatient.GetParamByIndex(0) = agent;
	agentHasPatient.GetParamByIndex(1) = patient;

	m_preconds->AddCondition(agentHasPatient);

	Condition agentAtLocative(OperatorLayoutType::OAOAB, OperatorType::EQUAL);
	
	agentAtLocative.GetParamByIndex(0) = agent;
	agentAtLocative.GetParamByIndex(0).attrib = AttributeType::ROOM;
	agentAtLocative.GetParamByIndex(1) = locative;
	agentAtLocative.GetParamByIndex(1).attrib = AttributeType::ROOM;

	m_preconds->AddCondition(agentAtLocative);

	/*Condition agentInventoryFull(OperatorLayoutType::OAVB, OperatorType::EQUAL);

	agentInventoryFull[0] = agent;
	agentInventoryFull[0].attrib = AttributeType::INVENTORY;
	agentInventoryFull[0].value = true;

	m_preconds->AddCondition(agentInventoryFull);*/

}

void Drop::InitEffects()
{
	Argument agent = *GetArg(SemanticRole::AGENT),
		patient = *GetArg(SemanticRole::PATIENT),
		locative = *GetArg(SemanticRole::LOCATIVE);

	Condition agentDoesNotHavePatient(OperatorLayoutType::OOB, OperatorType::HAS);
	agentDoesNotHavePatient.SetNegate(true);

	agentDoesNotHavePatient.GetParamByIndex(0) = agent;
	agentDoesNotHavePatient.GetParamByIndex(1) = patient;

	m_effects.push_back(agentDoesNotHavePatient);

	Condition patientAtLocative(OperatorLayoutType::OAOAB, OperatorType::EQUAL);
	
	patientAtLocative.GetParamByIndex(0) = patient;
	patientAtLocative.GetParamByIndex(0).attrib = AttributeType::ROOM;
	patientAtLocative.GetParamByIndex(1) = locative;
	patientAtLocative.GetParamByIndex(1).attrib = AttributeType::ROOM;

	m_effects.push_back(patientAtLocative);

	/*Condition agentInventoryEmpty(OperatorLayoutType::OAVB, OperatorType::EQUAL);

	agentInventoryEmpty[0] = agent;
	agentInventoryEmpty[0].attrib = AttributeType::INVENTORY;
	agentInventoryEmpty[0].value = false;

	m_effects.push_back(agentInventoryEmpty);*/
}

std::string Drop::Express(Agent* agent, Room* room)
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
	str << _agent << " dropped " << _patient;

	return str.str();
}

Drop::operator std::string()
{
	return "Drop";
}

float Drop::Cost(RoomManager* rm)
{
	// return a measure of
	// 1 - if that thing doesn't BELONG to you
	// 2 - bonus points if it BELONGS to someone else, and not a room

	float cost = 0;

	auto _agent = GetArg(SemanticRole::AGENT);
	auto _patient = GetArg(SemanticRole::PATIENT);
	auto _locative = GetArg(SemanticRole::LOCATIVE);


	if(_locative->instance->GetOwner() == 0)
	// If the room has no owner, i.e. public room
	{
		cost = 60.0f;
	}
	//else if(((Agent*)_locative->instance->GetOwner())->IsVictim())
	//// If the room has no owner, i.e. public room
	//{
	//	cost = 80;
	//}
	else if( _locative->instance->GetOwner() == _agent->instance )
	// if the room is the dropper's room
	{
		cost = 40.0f;
	}
	else if( _locative->instance->GetOwner() != _agent->instance )
	// if the room has an owner that isn't the dropper
	{
		cost = 20.0f + static_cast<float>(rand() % 10);
	}
	else if( _locative->instance->GetOwner() == _patient->instance->GetOwner() )
	// if the room belongs to the owner of the object
	{
		cost = 5.0f;
	}

	return cost;
}

void Drop::UpdateConditionInstances() // XXX
{
	Action::UpdateConditionInstances();
}

bool Drop::MightSatisfy(Condition& cond)
{
	return Action::MightSatisfy(cond);
}

void Drop::Debug()
{
}

void Drop::Dispatch(int turn)
{
	auto cp = GetArg(SemanticRole::AGENT);
	this->SetLogged();
	Agent* agent = dynamic_cast<Agent*>(cp->instance);
	Room* room = agent->GetRoom();
	
	for (Agent* agent : room->GetAgents())
	{
		if(agent->IsVictim() == false)
		{
			m_numWitness++;
		}
		
		if( agent != GetArg(SemanticRole::AGENT)->instance ) // Treat dropper differently
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
			Drop* drop = (Drop*)this->Clone();

			for(Agent* agent : room->GetAgents())
			{
				if(!agent->IsVictim() && agent != GetArg(SemanticRole::AGENT)->instance)
				{
					drop->GetArg(SemanticRole::AGENT)->instance = agent;
				}
			}
			Agent* falseAgent = (Agent*)cp->instance;
			falseAgent->Log(turn, drop);
			break;
		}
	default:
		// MORE THAN ONE PERSON SAW YOU
		// THIS IS NOT A GOOD SCENARIO
		break;
	};
}