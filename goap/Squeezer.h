#ifndef _GOAP_SQUEEZER_H_
#define _GOAP_SQUEEZER_H_

#include "Prop.h"

namespace GOAP
{
	class Squeezer : public Prop
	{
	public:
		Squeezer();
		Squeezer(std::string name);
		Squeezer(const Squeezer& other);
		~Squeezer();

		virtual operator ObjectType();
		virtual int GetCompoundType ();
		virtual bool CanBeMurderWeapon();
	};
}

#endif