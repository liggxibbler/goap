#include "Agent.h"
#include "Planner.h"

using namespace GOAP;

Agent::Agent()
{
	m_attribs[ATTRIB_TYPE_HEIGHT] = &m_height;
	m_attribs[ATTRIB_TYPE_WEIGHT] = &m_weight;
	m_attribs[ATTRIB_TYPE_ALIVE] = &m_isAlive;
	m_planner = new Planner();
	See(this); // Know thyself
}

Agent::Agent(char* name)
{
	m_name = name;
	m_attribs[ATTRIB_TYPE_HEIGHT] = &m_height;
	m_attribs[ATTRIB_TYPE_WEIGHT] = &m_weight;
	m_attribs[ATTRIB_TYPE_ALIVE] = &m_isAlive;
	m_planner = new Planner();
	See(this); // Know thyself
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

std::map<int, Object*>::iterator Agent::FirstObject()
{
	return m_objects.begin();
}

std::map<int, Object*>::iterator Agent::LastObject()
{
	return m_objects.end();
}

bool Agent::Unify(ObjectType ot, std::vector<Object*>& result)
{
	std::map<int, Object*>::iterator objIter;
	//iterate through list of objects
	for(objIter = m_objects.begin(); objIter != m_objects.end(); ++objIter)
	{
		//return if object.type = ot
		static Object* obj;
		obj = (*objIter).second;
		if(*obj == ot)
		{
			result.push_back(obj);
		}
	}
	
	if(result.empty())
	{
		return false;
	}

	return true;
}

void Agent::AddAction(ActionType at)
{
	m_actions.push_back(at);
}

void Agent::SetGoal(Goal* goal)
{
	m_goal = goal;
}

Plan* Agent::GetPlan(ActionManager* am, Op::OperatorManager* om)
{
	Plan* plan = new Plan();
	if( m_planner->Devise(this, am, om, plan) == PLAN_STAT_SUCCESS)
	{
		DUMP("FOUND PLAN")
	}
	return plan;
}

void Agent::See(Object* obj)
{
	m_objects[obj->GetID()] = obj;
}