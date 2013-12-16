#ifndef _GOAP_BLUNT_H_
#define _GOAP_BLUNT_H_

#include "Prop.h"

namespace GOAP
{
	class Blunt : public Prop
	{
	public:
		Blunt();
		Blunt(std::string name);
		Blunt(const Blunt& other);
		~Blunt();

		//virtual operator ObjectType();
		virtual int GetCompoundType ();
		virtual bool CanBeMurderWeapon();
	};
}

#endif