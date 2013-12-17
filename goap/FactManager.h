#ifndef _GOAP_FACTMANAGER_H_
#define _GOAP_FACTMANAGER_H_

#include <set>

namespace GOAP
{
	class Agent;
	class Room;

	class FactManager
	{
	public:
		Agent*	LastSeenBy(Agent* target, int turn);
		int		LastSeenAt(Agent* target, int turn);
		Room*	LastSeenIn(Agent* target, int turn);
		FactManager* Instance();
	private:
		FactManager();
		std::set<Agent*> m_agents;
	};
}

#endif