#include "Agent.h"

using namespace GOAP;

Agent::Agent()
{
	m_attribs[ATTRIB_TYPE_HEIGHT] = &m_height;
	m_attribs[ATTRIB_TYPE_WEIGHT] = &m_weight;
	m_attribs[ATTRIB_TYPE_ALIVE] = &m_isAlive;
}

Agent::Agent(const Agent& other)
{
}

Agent::~Agent()
{
}

Agent::operator GOAP::ObjectType()
{
	return OBJ_TYPE_AGENT;
}

Condition& Agent::Goal()
{
	return m_goal;
}

std::list<ActionType>::iterator Agent::FirstAction()
{
	return m_actions.begin();
}

std::list<ActionType>::iterator Agent::LastAction()
{
	return m_actions.end();
}