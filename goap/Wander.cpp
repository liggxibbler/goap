#include "Wander.h"
#include "World.h"
#include "GoTo.h"

using namespace GOAP;

Wander::Wander()
{
}

Wander::Wander(World* world, Agent* agent, int turns) : m_numTurns(turns), m_world(world), m_agent(agent)
{
}

Wander::Wander(const Wander& other)
{
}

Wander::~Wander()
{
}


Wander::operator ActionType()
{
	return ACTION_WANDER;
}

Wander* Wander::Clone()
{
	Wander* newWander = new Wander();
	newWander->CloneData(this);
	return newWander;
}

ActionStatus Wander::ExecuteWorkhorse()
{
	return ACT_STAT_DONE;
}

void Wander::InitArgs()
{
	ConditionParameter sub;
	
	// SUBJECT
	sub.semantic = OP_SEMANTIC_ROLE_AGENT;
	sub.instance = m_agent;
	sub.type = OBJ_TYPE_AGENT;
	m_args.push_back(sub);
}

void Wander::InitPreconditions()
{
	Condition condTrue(OP_LAYOUT_TYPE_TRUE, OPER_TYPE_TRUE);
	m_preconds->AddCondition(condTrue);
}

void Wander::InitEffects()
{
}