#ifndef _GOAP_STAB_H_
#define _GOAP_STAB_H_

#include "Action.h"
#include "Agent.h"

class Stab : public Action
{
public:
	Stab(Agent* subject, Agent* victim, Object* blade);
	virtual void Execute();
	virtual Stab* Clone();
private:

};

#endif