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
	return ACTION_DROP;
}

ExecutionStatus Drop::ExecuteWorkhorse(int turn)
{
	auto _agent(GetArg(SEMANTIC_ROLE_AGENT));
	auto _patient(GetArg(SEMANTIC_ROLE_PATIENT));

	Prop* patient = (Prop*)_patient->instance;
	patient->SetBearer(0);
	_agent->instance->GetRoom()->AddObject(patient);
	_agent->instance->SetAttribute(ATTRIBUTE_INVENTORY, false);

	DUMP("       ** " << Express(0, 0))
	return EXEC_STAT_SUCCESS;
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

	agent.semantic = SEMANTIC_ROLE_AGENT;
	agent.instance = NULL;
	agent.type = OBJ_TYPE_AGENT | OBJ_TYPE_OBJECT;
	agent.strict = true;
	m_args.push_back(agent);

	patient.semantic = SEMANTIC_ROLE_PATIENT;
	patient.instance = NULL;
	patient.type = OBJ_TYPE_PROP;
	patient.strict = false;
	m_args.push_back(patient);

	locative.semantic = SEMANTIC_ROLE_LOCATIVE;
	locative.instance = NULL;
	locative.type = OBJ_TYPE_ROOM | OBJ_TYPE_OBJECT;
	locative.strict = true;
	m_args.push_back(locative);
}

void Drop::InitPreconditions()
{
	Argument agent = *GetArg(SEMANTIC_ROLE_AGENT),
		patient = *GetArg(SEMANTIC_ROLE_PATIENT),
		locative = *GetArg(SEMANTIC_ROLE_LOCATIVE);

	Condition agentHasPatient(OP_LAYOUT_TYPE_OOB, OPERATOR_HAS);

	agentHasPatient[0] = agent;
	agentHasPatient[1] = patient;

	m_preconds->AddCondition(agentHasPatient);

	Condition agentAtLocative(OP_LAYOUT_TYPE_OAOAB, OPERATOR_EQUAL);
	
	agentAtLocative[0] = agent;
	agentAtLocative[0].attrib = ATTRIBUTE_ROOM;
	agentAtLocative[1] = locative;
	agentAtLocative[1].attrib = ATTRIBUTE_ROOM;

	m_preconds->AddCondition(agentAtLocative);

	/*Condition agentInventoryFull(OP_LAYOUT_TYPE_OAVB, OPERATOR_EQUAL);

	agentInventoryFull[0] = agent;
	agentInventoryFull[0].attrib = ATTRIBUTE_INVENTORY;
	agentInventoryFull[0].value = true;

	m_preconds->AddCondition(agentInventoryFull);*/

}

void Drop::InitEffects()
{
	Argument agent = *GetArg(SEMANTIC_ROLE_AGENT),
		patient = *GetArg(SEMANTIC_ROLE_PATIENT),
		locative = *GetArg(SEMANTIC_ROLE_LOCATIVE);

	Condition agentDoesNotHavePatient(OP_LAYOUT_TYPE_OOB, OPERATOR_HAS);
	agentDoesNotHavePatient.SetNegate(true);

	agentDoesNotHavePatient[0] = agent;
	agentDoesNotHavePatient[1] = patient;

	m_effects.push_back(agentDoesNotHavePatient);

	Condition patientAtLocative(OP_LAYOUT_TYPE_OAOAB, OPERATOR_EQUAL);
	
	patientAtLocative[0] = patient;
	patientAtLocative[0].attrib = ATTRIBUTE_ROOM;
	patientAtLocative[1] = locative;
	patientAtLocative[1].attrib = ATTRIBUTE_ROOM;

	m_effects.push_back(patientAtLocative);

	/*Condition agentInventoryEmpty(OP_LAYOUT_TYPE_OAVB, OPERATOR_EQUAL);

	agentInventoryEmpty[0] = agent;
	agentInventoryEmpty[0].attrib = ATTRIBUTE_INVENTORY;
	agentInventoryEmpty[0].value = false;

	m_effects.push_back(agentInventoryEmpty);*/
}

std::string Drop::Express(Agent* agent, Room* room)
{
	auto sub = GetArg(SEMANTIC_ROLE_AGENT);
	auto obj = GetArg(SEMANTIC_ROLE_PATIENT);

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

int Drop::Cost(RoomManager* rm)
{
	// return a measure of
	// 1 - if that thing doesn't BELONG to you
	// 2 - bonus points if it BELONGS to someone else, and not a room

	int cost = 0;

	auto _agent = GetArg(SEMANTIC_ROLE_AGENT);
	auto _patient = GetArg(SEMANTIC_ROLE_PATIENT);
	auto _locative = GetArg(SEMANTIC_ROLE_LOCATIVE);


	if(_locative->instance->GetOwner() == 0)
	// If the room has no owner, i.e. public room
	{
		cost = 60;
	}
	//else if(((Agent*)_locative->instance->GetOwner())->IsVictim())
	//// If the room has no owner, i.e. public room
	//{
	//	cost = 80;
	//}
	else if( _locative->instance->GetOwner() == _agent->instance )
	// if the room is the dropper's room
	{
		cost = 40;
	}
	else if( _locative->instance->GetOwner() != _agent->instance )
	// if the room has an owner that isn't the dropper
	{
		cost = 20 + rand() % 10;
	}
	else if( _locative->instance->GetOwner() == _patient->instance->GetOwner() )
	// if the room belongs to the owner of the object
	{
		cost = 5;
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
	auto cp = GetArg(SEMANTIC_ROLE_AGENT);
	this->SetLogged();
	Agent* agent = dynamic_cast<Agent*>(cp->instance);
	Room* room = agent->GetRoom();
	
	for(auto agent(room->GetFirstAgent());agent != room->GetLastAgent();++agent)
	{
		if((*agent)->IsVictim() == false)
		{
			m_numWitness++;
		}
		if( (*agent) != GetArg(SEMANTIC_ROLE_AGENT)->instance ) // Treat dropper differently
		{
			(*agent)->Log(turn, this);
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
			for(auto agent(room->GetFirstAgent());agent != room->GetLastAgent();++agent)
			{
				if(!(*agent)->IsVictim() && (*agent) != GetArg(SEMANTIC_ROLE_AGENT)->instance)
				{
					drop->GetArg(SEMANTIC_ROLE_AGENT)->instance = *agent;
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