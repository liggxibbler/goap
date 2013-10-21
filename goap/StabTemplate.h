#ifndef _GOAP_STABTEMPLATE_H_
#define _GOAP_STABTEMPLATE_H_

#include "ActionTemplate.h"
#include "Stab.h"

class StabTemplate : public ActionTemplate
{
public:
	StabTemplate();
	StabTemplate(const StabTemplate& other);
	~StabTemplate();

	virtual Action* CreateNew();
};

#endif