#ifndef _GOAP_PROJECTILE_H_
#define _GOAP_PROJECTILE_H_

#include "Object.h"

namespace GOAP
{
	class Projectile : public Object
	{
	public:
		Projectile();
		Projectile(std::string name);
		Projectile(const Projectile& other);
		~Projectile();

		virtual operator ObjectType();
		virtual int GetCompoundType ();
		virtual bool CanBeMurderWeapon();
	};
}

#endif