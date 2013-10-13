#ifndef _GOAP_OPERATOR_H_
#define _GOAP_OPERATOR_H_

#include "Common.h"
#include "Object.h"
#include "ConcreteCondition.h"

namespace GOAP
{
	class Operator
	{
	public:
		Operator();
		Operator(const Operator& other);
		~Operator();

		// might make non-pure virtual, for exception handling...

		bool Evaluate(ConcreteCondition cc);

		virtual bool operator() (Object* obj, AttributeType attrib, int val, bool neg) = 0;
		virtual bool operator() (Object* obj1, Object* obj2, AttributeType attrib, bool neg) = 0;
		virtual bool operator() (Object* obj1, AttributeType attrib1, Object* obj2, AttributeType attrib2, bool neg) = 0;
		virtual bool operator() (Object* obj1, Object* obj2, bool neg) = 0;

	private:
	};
};

#endif