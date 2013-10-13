#ifndef _GOAP_OPERATOR_H_
#define _GOAP_OPERATOR_H_

namespace GOAP
{
	class Object;
	enum Attribute;

	class Operator
	{
	public:
		enum Layout
		{
			/*
			O for Object
			A for Attribute
			V for Value
			B indicates the boolean that can negate the result
			*/
			OAVB,	// O has attrib A with query V e.g. O.height == 160
			OOAB,	// O1 and O2 have attribute A compared e.g. O1.weight > O2.weight
			OAOAB,	// O1 has attrib A1, O2 has attrib A2, compared e.g. O1.strength > O2.weight
			OOB		// O1 and O2 have object level relationship e.g. O1 owns O2
		};
	public:
		Operator();
		Operator(const Operator& other);
		~Operator();

		bool operator() (Object obj, Attribute attrib, int val, bool neg);
		bool operator() (Object obj1, Object obj2, Attribute attrib, bool neg);
		bool operator() (Object obj1, Attribute attrib1, Object obj2, Attribute attrib2, bool neg);
		bool operator() (Object obj1, Object obj2, bool neg);

	private:
	};
};

#endif