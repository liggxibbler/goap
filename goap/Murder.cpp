#include "Murder.h"
#include "RoomManager.h"
#include "Room.h"
#include "FactManager.h"

using namespace GOAP;

ExecutionStatus Murder::ExecuteWorkhorse(int turn)
{
	ConditionParameter sub(*GetArg(SEMANTIC_ROLE_AGENT));
	ConditionParameter obj(*GetArg(SEMANTIC_ROLE_PATIENT));
	ConditionParameter ins(*GetArg(SEMANTIC_ROLE_INSTRUMENT));
	ConditionParameter loc(*GetArg(SEMANTIC_ROLE_LOCATIVE));

	if(true)//loc.instance->GetAttrib(ATTRIBUTE_NUM_AGENTS) <= 3)
	{
		DUMP("       ** " << Express(0, 0))

			obj.instance->SetAttribute(ATTRIBUTE_ALIVE, false);
		Agent* agent = (Agent*)(sub.instance);
		agent->DoneMurder(true);

		Goal* loseMurderWeapon = new Goal;

		Condition notHaveMurderWeapon(OP_LAYOUT_TYPE_OOB, OPERATOR_HAS);
		notHaveMurderWeapon.SetNegate(true);
		notHaveMurderWeapon[0] = *GetArg(SEMANTIC_ROLE_AGENT);
		notHaveMurderWeapon[1] = *GetArg(SEMANTIC_ROLE_INSTRUMENT);
		loseMurderWeapon->AddCondition(notHaveMurderWeapon);
		loseMurderWeapon->SetPriority(21);

		agent->AddGoal(loseMurderWeapon);

		return EXEC_STAT_MURDER;
	}
	else
	{
		return EXEC_STAT_RUNNING;
	}
}

void Murder::InitArgs()
{
	ConditionParameter agent, patient, room;

	// AGENT
	agent.semantic = SEMANTIC_ROLE_AGENT;
	agent.instance = NULL;
	agent.type = OBJ_TYPE_AGENT | OBJ_TYPE_OBJECT;
	agent.strict = true;
	m_args.push_back(agent);

	// PATIENT
	patient.semantic = SEMANTIC_ROLE_PATIENT;
	patient.instance = NULL;
	patient.type = OBJ_TYPE_AGENT | OBJ_TYPE_OBJECT;
	patient.strict = true;
	m_args.push_back(patient);

	// LOCATIVE
	room.semantic = SEMANTIC_ROLE_LOCATIVE;
	room.instance = NULL;
	room.type = OBJ_TYPE_ROOM | OBJ_TYPE_OBJECT;
	room.strict = true;
	m_args.push_back(room);
}

void Murder::InitEffects()
{
	Condition objIsDead(OP_LAYOUT_TYPE_OAVB, OPERATOR_EQUAL);
	ConditionParameter obj = *GetArg(SEMANTIC_ROLE_PATIENT);

	objIsDead[0] = obj;
	objIsDead[0].attrib	= ATTRIBUTE_ALIVE;
	objIsDead[0].value	= false;
	objIsDead.SetNegate(false);

	m_effects.push_back(objIsDead);
}

void Murder::InitPreconditions()
{
	auto _agent(GetArg(SEMANTIC_ROLE_AGENT));
	auto _patient(GetArg(SEMANTIC_ROLE_PATIENT));
	auto _instrument(GetArg(SEMANTIC_ROLE_INSTRUMENT));
	auto _locative(GetArg(SEMANTIC_ROLE_LOCATIVE));

	// AGENT owns INSTRUMENT
	Condition agentHasInst(OP_LAYOUT_TYPE_OOB, OPERATOR_HAS);

	agentHasInst[0] = *_agent;
	agentHasInst[1] = *_instrument;

	m_preconds->AddCondition(agentHasInst);

	// AGENT AT LOCATIVE

	Condition agentAtLoc(OP_LAYOUT_TYPE_OAOAB, OPERATOR_EQUAL);

	agentAtLoc[0] = *_agent;
	agentAtLoc[0].attrib = ATTRIBUTE_ROOM;

	agentAtLoc[1] = *_locative;
	agentAtLoc[1].attrib = ATTRIBUTE_ROOM;

	m_preconds->AddCondition(agentAtLoc);

	// PATIENT AT LOCATIVE

	Condition patientAtLoc(OP_LAYOUT_TYPE_OAOAB, OPERATOR_EQUAL);

	patientAtLoc[0] = *_patient;
	patientAtLoc[0].attrib = ATTRIBUTE_ROOM;

	patientAtLoc[1] = *_locative;
	patientAtLoc[1].attrib = ATTRIBUTE_ROOM;

	m_preconds->AddCondition(patientAtLoc);

	// AGENT ALONE WITH PATIENT

	/*Condition agentAloneWithPatient(OP_LAYOUT_TYPE_OAVB, OPERATOR_EQUAL);

	agentAloneWithPatient[0] = *_locative;
	agentAloneWithPatient[0].attrib = ATTRIBUTE_NUM_AGENTS;
	agentAloneWithPatient[0].value = 2;

	m_preconds->AddCondition(agentAloneWithPatient);*/

}

int Murder::Cost(RoomManager* rm)
{
	// return a measure of
	// 1 - how UNLIKELY it is to find the victim alone in the room
	// 2 - how UNLIKELY it is for the victim to be found after being killed
	// 3 - number of instances of instrument class
	// 4 - owner of instrument

	int cost = 0;

	auto _patient = GetArg(SEMANTIC_ROLE_PATIENT);
	auto _locative = GetArg(SEMANTIC_ROLE_LOCATIVE);
	auto _instrument = GetArg(SEMANTIC_ROLE_INSTRUMENT);

	Object* roomOwner = _locative->instance->GetOwner();
	
	Prop* inst = (Prop*)(_instrument->instance);

	// Prefer instruments with many instances
	cost += 10 / ( 1 + inst->GetNumberOfInstances() );

	if (roomOwner != 0)
	{
		// penalty for suspicious activity
		cost += 500 * rm->GetProb((Agent*)roomOwner, (Room*)_locative->instance);
	}
	if (roomOwner == _patient->instance)
	{
		// penalty for suspicious activity
		cost += 500;
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
	GetArg(SEMANTIC_ROLE_AGENT)->instance = agent;
	GetArg(SEMANTIC_ROLE_PATIENT)->instance = patient;
	GetArg(SEMANTIC_ROLE_INSTRUMENT)->instance = instrument;
	GetArg(SEMANTIC_ROLE_LOCATIVE)->instance = locative;
}

void Murder::Dispatch(int turn)
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
		if( ! (*agent)->IsMurderer() ) // Treat murdere differently
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
			Murder* murder = (Murder*)this->Clone();
			for(auto agent(room->GetFirstAgent());agent != room->GetLastAgent();++agent)
			{
				if(!(*agent)->IsVictim() && !(*agent)->IsMurderer())
				{
					murder->GetArg(SEMANTIC_ROLE_AGENT)->instance = *agent;
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
	
	Condition notHaveMurderWeapon(OP_LAYOUT_TYPE_OOB, OPERATOR_HAS);
	notHaveMurderWeapon.SetNegate(true);
	notHaveMurderWeapon[0] = *GetArg(SEMANTIC_ROLE_AGENT);
	notHaveMurderWeapon[1] = *GetArg(SEMANTIC_ROLE_INSTRUMENT);
	loseMurderWeapon->AddCondition(notHaveMurderWeapon);
	loseMurderWeapon->SetPriority(19);

	return loseMurderWeapon;
}