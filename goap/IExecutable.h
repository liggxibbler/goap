#ifndef _GOAP_EXECUTABLE_H_
#define _GOAP_EXECUTABLE_H_

#include "Common.h"

namespace GOAP
{
	namespace Op
	{
		class OperatorManager;
	}
	class IExecutable
	{
	public:
		virtual ExecutionStatus Execute(Op::OperatorManager* om, int turn) = 0;
	};
}
#endif