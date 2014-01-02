#ifndef _GOAP_EXECUTABLE_H_
#define _GOAP_EXECUTABLE_H_

#include "Common.h"

namespace GOAP
{
	class Goal;
	namespace Op
	{
		class OperatorManager;
	}
	class IExecutable
	{
	public:
		virtual ExecutionStatus Execute(Op::OperatorManager* om, int turn) = 0;
		virtual Goal* FollowupGoal() = 0;
		//virtual void Pause() = 0;
		//virtual void Resume() = 0;
	};
}
#endif