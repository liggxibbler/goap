#ifndef _GOAP_BLADE_H_
#define _GOAP_BLADE_H_

#include "Object.h"

namespace GOAP
{
	class Blade : public Object
	{
	public:
		Blade();
		Blade(std::string name);
		Blade(const Blade& other);
		~Blade();

		virtual operator ObjectType();
		virtual int GetCompoundType ();
	};
}

#endif