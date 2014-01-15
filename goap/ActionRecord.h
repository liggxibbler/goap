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
		ss << (turns * 10 / 60 + 18) % 24;
		ss.width(1);
		ss << ":";
		ss.width(2);
		ss << turns * 10 % 60;
		return ss.str();
	}

	inline std::string TURN2INTERVAL(int turn)
	{
		std::stringstream ss;
		ss << "between ";
		ss.fill('0');
		ss.width(2);
		ss << (turn * 10 / 60 + 18) % 24;
		ss << ":00";
		ss.width(1);
		ss << " and ";
		ss.width(2);
		ss << (turn * 10 / 60 + 18 + 1) % 24;
		ss << ":00";
		return ss.str();
	}
}
#endif