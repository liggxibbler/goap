#ifndef _GOAP_AGENT_H_
#define _GOAP_AGENT_H_

#include "ActionTemplate.h"
#include "Object.h"

namespace GOAP
{
	class Agent : public Object
	{
	public:
		Agent();
		/*{
			m_attribs[HEIGHT] = &m_height;
			m_attribs[WEIGHT] = &m_weight;
			m_attribs[ALIVE] = &m_isAlive;
		}*/
	private:
		int m_height;
		int m_weight;
		int m_isAlive;
	};
}

#endif