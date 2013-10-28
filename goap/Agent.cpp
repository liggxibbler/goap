#include "Agent.h"

using namespace GOAP;

Agent::Agent()
{
	m_attribs[ATTRIB_TYPE_HEIGHT] = &m_height;
	m_attribs[ATTRIB_TYPE_WEIGHT] = &m_weight;
	m_attribs[ATTRIB_TYPE_ALIVE] = &m_isAlive;
}

Agent::Agent(char* name)
{
	m_name = name;
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

std::list<Object*>::iterator Agent::FirstObject()
{
	return m_objects.begin();
}

std::list<Object*>::iterator Agent::LastObject()
{
	return m_objects.end();
}

bool Agent::Unify(ObjectType ot, std::vector<Object*>& result)
{
	std::list<Object*>::iterator objIter;
	//iterate through list of objects
	for(objIter = m_objects.begin(); objIter != m_objects.end(); ++objIter)
	{
		//return if object.type = ot
		if(*(*objIter) == ot)
		{
			result.push_back(*objIter);
		}
	}
	
	if(result.empty())
	{
		return false;
	}

	return true;
}