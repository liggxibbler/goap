#ifndef _GOAP_BLADE_H_
#define _GOAP_BLADE_H_

#include "Prop.h"

namespace GOAP
{
	class Blade : public Prop
	{
	public:
		Blade();
		Blade(std::string name);
		Blade(const Blade& other);
		~Blade();

		//virtual operator ObjectType();
		virtual int GetCompoundType ();
		virtual bool CanBeMurderWeapon();

		virtual void IncreaseValue();
		virtual int GetValue();

	private:
		static int s_value;
	};
}

#endif