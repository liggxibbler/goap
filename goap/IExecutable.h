#ifndef _GOAP_EXECUTABLE_H_
#define _GOAP_EXECUTABLE_H_

#include "Common.h"

namespace GOAP
{
	class IExecutable
	{
	public:
		virtual ActionStatus Execute() = 0;
	};
}
#endif