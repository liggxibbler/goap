#include "FactManager.h"
#include "Agent.h"

using namespace GOAP;

void FactManager::Initialize(std::vector<Agent*>& agents)
{
	for(auto agent(agents.begin()); agent != agents.end(); ++agent)
	{
		m_agents.insert(*agent);
	}

	//	latestTime = 0
	unsigned int latestTime = 0;
	//// extract latest event time
	for(auto agent(m_agents.begin()); agent != m_agents.end();++agent)
	//	for each agent
	//		if latestTime < agent.lastRecord.turn
	//			latestTime = agent.lastRecord.turn
	{
		unsigned int numRecords = (*agent)->m_actionLog.size();
		unsigned int iTime = (*agent)->m_actionLog[numRecords-1].turn;
		if(iTime > latestTime)
		{
			latestTime = iTime;
		}
	}
	
	//// populate table
	//	for each agent
	//		lastTime = 0
	//		for each event
	//			time = event.turn
	//			chart[agent][time] = room;
	//			if time - lastTime > 1:
	//				for all turns in between
	//					chart[agent][turn] = chart[agent][lastTurn];
	//			lastTime = time;
	//		if lastTime < latestTime
	//			for all turns to the end
	//				chart[agent][turn] = chart[agent][lastTime]
	for(auto agent(m_agents.begin()); agent != m_agents.end(); ++agent)
	{
		int lastTime = 0;
		for(int event_ = 0; event_ < (*agent)->m_actionLog.size(); ++event_)
		{
			int time = (*agent)->m_actionLog[event_].turn;
			m_roomChart[*agent][time] = (*agent)->m_actionLog[event_].room;
			if( time - lastTime > 1)
			{
				for(int timeInBetween = lastTime + 1; timeInBetween < time ; ++timeInBetween)
				{
					m_roomChart[*agent][timeInBetween] = (*agent)->m_actionLog[event_].room;
				}
			}
			lastTime = time;
		}
		if(lastTime < latestTime)
		{
			for(int timeInBetween = lastTime + 1; timeInBetween < latestTime ; ++timeInBetween)
			{
				m_roomChart[*agent][timeInBetween] = m_roomChart[*agent][lastTime];
			}
		}
	}
}

bool	FactManager::LastSeen(Agent* target, int turn, SeenRecord& sr)
{
	//	for time = turn, step back
	//		for each agent in m_agents
	//			if chart[agent][time] == chart[target][time]
	//				flag found time and room
	//	for each agent in m_agents
	//		if chart[agent][time] == chart[target][time]
	//	return agent, time // but this is worng if there are multiple agents
	
	bool foundTime = false;
	for(int time = turn; time >=0 && !foundTime; --time)
	{
		for(auto agent(m_agents.begin()); agent != m_agents.end() && !foundTime ; ++agent)
		{
			if(m_roomChart[*agent][time] == m_roomChart[target][time])
			{
				sr.when = time;
				sr.where_ = m_roomChart[target][time];
				foundTime = true;
			}
		}
	}
	
	for(auto agent(m_agents.begin()); agent != m_agents.end() && !foundTime ; ++agent)
	{
		if(m_roomChart[*agent][sr.when] == m_roomChart[target][sr.when])
		{
			sr.who.push_back(*agent);
		}
	}

	return foundTime;
}

FactManager* FactManager::Instance()
{
	static FactManager fm;
	return &fm;
}

FactManager::FactManager()
{
}

Room* FactManager::GetRoom (Agent* agent, int turn)
{
	return m_roomChart[agent][turn];
}