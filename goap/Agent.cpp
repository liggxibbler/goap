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

Goal* Agent::GetGoal()
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

//std::list<Object*>::iterator Agent::Unify(ObjectType ot, std::list<Object*>::iterator from)
//{
//	//iterate through list of objects
//	//return if object.type = ot
//	// BUT remember where you left so you can come back
//}