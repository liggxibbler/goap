#ifndef _GOAP_STABTEMPLATE_H_
#define _GOAP_STABTEMPLATE_H_

#include "ActionTemplate.h"
#include "Stab.h"
#include "AbstractCondition.h"

namespace GOAP
{
	class StabTemplate : public ActionTemplate
	{
	public:
		StabTemplate();
		StabTemplate(const StabTemplate& other);
		~StabTemplate();
	};
}
#endif