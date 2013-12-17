#ifndef _GOAP_ACTIONRECORD_H_
#define _GOAP_ACTIONRECORD_H_

#include <sstream>
#include <string>

namespace GOAP
{
	class Action;

	struct ActionRecord
	{
		int turn;
		Action* action;
		Room* roomSnap;
		Room* room;
	};

	inline std::string TURN2TIME(int turns)
	{
		std::stringstream ss;
		ss.fill('0');
		ss.width(2);
		ss << turns * 10 / 60;
		ss.width(1);
		ss << ":";
		ss.width(2);
		ss << turns * 10 % 60;
		return ss.str();
	}
}
#endif