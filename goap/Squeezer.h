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

		//virtual operator ObjectType();
		virtual int GetCompoundType ();
		virtual bool CanBeMurderWeapon();

		virtual void IncreaseValue();
		virtual int GetValue();
		virtual int GetNumberOfInstances();

	private:
		static int s_value;
		static int s_numInstances;
	};
}

#endif