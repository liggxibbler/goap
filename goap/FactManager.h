#ifndef _GOAP_FACTMANAGER_H_
#define _GOAP_FACTMANAGER_H_

#include <set>
#include <map>
#include <vector>

namespace GOAP
{
	class Agent;
	class Room;

	class FactManager
	{
	public:

		struct SeenRecord
		{
		public:
			Agent* who;
			int when;
			Room* where_;
			SeenRecord():who(0), when(0), where_(0)
			{
			}
		};

		SeenRecord	LastSeen(Agent* target, int turn);
		FactManager* Instance();

		void Initialize(std::vector<Agent*>& agents);

	private:
		FactManager();
		std::set<Agent*> m_agents;
		std::map< Agent*, std::map< int, Room*> > m_roomChart;
	};
}

#endif