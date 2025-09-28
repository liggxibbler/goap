#include "Murder.h"
#include "RoomManager.h"
#include "Room.h"
#include "FactManager.h"

using namespace GOAP;

ExecutionStatus Murder::ExecuteWorkhorse(int turn)
{
	Argument sub(*GetArg(SemanticRole::AGENT));
	Argument obj(*GetArg(SemanticRole::PATIENT));
	Argument ins(*GetArg(SemanticRole::INSTRUMENT));
	Argument loc(*GetArg(SemanticRole::LOCATIVE));

	if(true)//loc.instance->GetAttrib(AttributeType::NUM_AGENTS) <= 3)
	{
		DUMP("       ** " << Express(0, 0))

			obj.instance->SetAttribute(AttributeType::ALIVE, false);
		Agent* agent = (Agent*)(sub.instance);
		agent->DoneMurder(true);

		Goal* loseMurderWeapon = new Goal;

		Condition notHaveMurderWeapon(OperatorLayoutType::OOB, OperatorType::HAS);
		notHaveMurderWeapon.SetNegate(true);
		notHaveMurderWeapon.GetParamByIndex(0) = *GetArg(SemanticRole::AGENT);
		notHaveMurderWeapon.GetParamByIndex(1) = *GetArg(SemanticRole::INSTRUMENT);
		loseMurderWeapon->AddCondition(notHaveMurderWeapon);
		loseMurderWeapon->SetPriority(21);

		agent->AddGoal(loseMurderWeapon);

		return ExecutionStatus::MURDER;
	}
	else
	{
		return ExecutionStatus::RUNNING;
	}
}

void Murder::InitArgs()
{
	Argument agent, patient, room;

	// AGENT
	agent.semantic = SemanticRole::AGENT;
	agent.instance = nullptr;
	agent.type = ObjectType::AGENT | ObjectType::OBJECT;
	agent.strict = true;
	m_args.push_back(agent);

	// PATIENT
	patient.semantic = SemanticRole::PATIENT;
	patient.instance = nullptr;
	patient.type = ObjectType::AGENT | ObjectType::OBJECT;
	patient.strict = true;
	m_args.push_back(patient);

	// LOCATIVE
	room.semantic = SemanticRole::LOCATIVE;
	room.instance = nullptr;
	room.type = ObjectType::ROOM | ObjectType::OBJECT;
	room.strict = true;
	m_args.push_back(room);
}

void Murder::InitEffects()
{
	Condition objIsDead(OperatorLayoutType::OAVB, OperatorType::EQUAL);
	Argument obj = *GetArg(SemanticRole::PATIENT);

	objIsDead.GetParamByIndex(0) = obj;
	objIsDead.GetParamByIndex(0).attrib	= AttributeType::ALIVE;
	objIsDead.GetParamByIndex(0).value	= false;
	objIsDead.SetNegate(false);

	m_effects.push_back(objIsDead);
}

void Murder::InitPreconditions()
{
	auto _agent(GetArg(SemanticRole::AGENT));
	auto _patient(GetArg(SemanticRole::PATIENT));
	auto _instrument(GetArg(SemanticRole::INSTRUMENT));
	auto _locative(GetArg(SemanticRole::LOCATIVE));

	// AGENT owns INSTRUMENT
	Condition agentHasInst(OperatorLayoutType::OOB, OperatorType::HAS);

	agentHasInst.GetParamByIndex(0) = *_agent;
	agentHasInst.GetParamByIndex(1) = *_instrument;

	m_preconds->AddCondition(agentHasInst);

	// AGENT AT LOCATIVE

	Condition agentAtLoc(OperatorLayoutType::OAOAB, OperatorType::EQUAL);

	agentAtLoc.GetParamByIndex(0) = *_agent;
	agentAtLoc.GetParamByIndex(0).attrib = AttributeType::ROOM;

	agentAtLoc.GetParamByIndex(1) = *_locative;
	agentAtLoc.GetParamByIndex(1).attrib = AttributeType::ROOM;

	m_preconds->AddCondition(agentAtLoc);

	// PATIENT AT LOCATIVE

	Condition patientAtLoc(OperatorLayoutType::OAOAB, OperatorType::EQUAL);

	patientAtLoc.GetParamByIndex(0) = *_patient;
	patientAtLoc.GetParamByIndex(0).attrib = AttributeType::ROOM;

	patientAtLoc.GetParamByIndex(1) = *_locative;
	patientAtLoc.GetParamByIndex(1).attrib = AttributeType::ROOM;

	m_preconds->AddCondition(patientAtLoc);

	// AGENT ALONE WITH PATIENT

	/*Condition agentAloneWithPatient(OperatorLayoutType::OAVB, OperatorType::EQUAL);

	agentAloneWithPatient[0] = *_locative;
	agentAloneWithPatient[0].attrib = AttributeType::NUM_AGENTS;
	agentAloneWithPatient[0].value = 2;

	m_preconds->AddCondition(agentAloneWithPatient);*/

}

float Murder::Cost(RoomManager* rm)
{
	// return a measure of
	// 1 - how UNLIKELY it is to find the victim alone in the room
	// 2 - how UNLIKELY it is for the victim to be found after being killed
	// 3 - number of instances of instrument class
	// 4 - owner of instrument

	float cost = 0;

	auto _patient = GetArg(SemanticRole::PATIENT);
	auto _locative = GetArg(SemanticRole::LOCATIVE);
	auto _instrument = GetArg(SemanticRole::INSTRUMENT);

	Object* roomOwner = _locative->instance->GetOwner();
	
	Prop* inst = (Prop*)(_instrument->instance);

	// Prefer instruments with many instances
	cost += 10.0f / ( 1 + inst->GetNumberOfInstances() );

	if (roomOwner != 0)
	{
		// penalty for suspicious activity
		cost += 500.0f * rm->GetProb((Agent*)roomOwner, (Room*)_locative->instance);
	}
	if (roomOwner == _patient->instance)
	{
		// penalty for suspicious activity
		cost += 500.0f;
	}

	// penalty for risk of not being found
	cost += 1000.0f * (1.0f - rm->GetProbWillBeFound((Agent*)_patient->instance, (Room*)_locative->instance));

	// penalty for risk of not finding victim alone
	cost += 1000.f * (1.0f - rm->GetProbAlone((Agent*)_patient->instance, (Room*)_locative->instance));

	return cost;

	//return rand() % 1000;
}

void Murder::SetArguments(Agent* agent, Agent* patient, Object* instrument, Room* locative)
{
	GetArg(SemanticRole::AGENT)->instance = agent;
	GetArg(SemanticRole::PATIENT)->instance = patient;
	GetArg(SemanticRole::INSTRUMENT)->instance = instrument;
	GetArg(SemanticRole::LOCATIVE)->instance = locative;
}

void Murder::Dispatch(int turn)
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
			Murder* murder = (Murder*)this->Clone();
			for (Agent* agent : room->GetAgents())
			{
				if(!agent->IsVictim() && !agent->IsMurderer())
				{
					murder->GetArg(SemanticRole::AGENT)->instance = agent;
				}
			}
			Agent* falseAgent = (Agent*)cp->instance;
			falseAgent->Log(turn, murder);
			break;
		}
	default:
		// MORE THAN ONE PERSON SAW YOU
		// THIS IS NOT A GOOD SCENARIO
		break;
	};
}

Goal* Murder::FollowupGoal()
{
		// Make murderer drop murder weapon
	Goal* loseMurderWeapon = new Goal;
	
	Condition notHaveMurderWeapon(OperatorLayoutType::OOB, OperatorType::HAS);
	notHaveMurderWeapon.SetNegate(true);
	notHaveMurderWeapon.GetParamByIndex(0) = *GetArg(SemanticRole::AGENT);
	notHaveMurderWeapon.GetParamByIndex(1) = *GetArg(SemanticRole::INSTRUMENT);
	loseMurderWeapon->AddCondition(notHaveMurderWeapon);
	loseMurderWeapon->SetPriority(19);

	return loseMurderWeapon;
}