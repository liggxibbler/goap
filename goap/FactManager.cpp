#include "FactManager.h"
#include "Agent.h"

using namespace GOAP;

void FactManager::Initialize(std::vector<Agent*>& agents)
{
	//	extract time of latest recorded event, latestTime
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
}

FactManager::SeenRecord	FactManager::LastSeen(Agent* target, int turn)
{

}

FactManager* FactManager::Instance()
{
	static FactManager fm;
	return &fm;
}