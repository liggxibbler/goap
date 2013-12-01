#ifndef _GOAP_ACTIONRECORD_H_
#define _GOAP_ACTIONRECORD_H_

namespace GOAP
{
	class Action;

	struct ActionRecord
	{
		int turn;
		Action* action;
	};
}
#endif