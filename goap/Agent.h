#ifndef _GOAP_AGENT_H_
#define _GOAP_AGENT_H_

//#include "ActionTemplate.h"
#include "Object.h"

namespace GOAP
{
	class Agent : public Object
	{
	public:
		Agent();
		Agent(const Agent& other);
		~Agent();

	private:
		int m_height;
		int m_weight;
		int m_isAlive;
	};
}

#endif