#ifndef _GOAP_AGENT_H_
#define _GOAP_AGENT_H_

#include "ActionTemplate.h"
#include "Object.h"

namespace GOAP
{
	class Agent : public Object
	{
	public:

	private:
		ActionTemplate* m_actionTemplates;
	};
}

#endif