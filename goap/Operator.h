#ifndef _GOAP_OPERATOR_H_
#define _GOAP_OPERATOR_H_

#include "Common.h"

namespace GOAP
{
	class Object;
	enum Attribute;

	class Operator
	{
	public:
		Operator();
		Operator(const Operator& other);
		~Operator();

		// might make non-pure virtual, for exception handling...

		virtual bool operator() (Object obj, Attribute attrib, int val, bool neg) = 0;
		virtual bool operator() (Object obj1, Object obj2, Attribute attrib, bool neg) = 0;
		virtual bool operator() (Object obj1, Attribute attrib1, Object obj2, Attribute attrib2, bool neg) = 0;
		virtual bool operator() (Object obj1, Object obj2, bool neg) = 0;

	private:
	};
};

#endif