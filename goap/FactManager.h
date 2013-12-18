#ifndef _GOAP_FACTMANAGER_H_
#define _GOAP_FACTMANAGER_H_

#include <list>
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
			std::list<Agent*> who;
			int when;
			Room* where_;
			SeenRecord():who(0), when(0), where_(0)
			{
			}
		};

		bool	LastSeen(Agent* target, int turn, SeenRecord& sr);
		static FactManager* Instance();

		void Initialize(std::vector<Agent*>& agents);

		Room* GetRoom (Agent* agent, int turn);

	private:
		FactManager();
		std::set<Agent*> m_agents;
		std::map< Agent*, std::map< int, Room*> > m_roomChart;
	};
}

#endif