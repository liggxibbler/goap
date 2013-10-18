#ifndef _GOAP_COMMONS_H_
#define _GOAP_COMMONS_H_

#include <iostream>
#ifdef _DEBUG
#define DUMP(X) std::cout << std::endl << X << std::endl;
#else
#define DUMP(X)
#endif

namespace GOAP
{
	//template <class T>
	//class CappedStack
	//{
	//public:
	//	CappedStack()
	//	{
	//		m_top = 0;
	//		m_numItems = 0;
	//		m_items = 0;
	//	}

	//	CappedStack(int numItems)
	//	{
	//		m_top = 0;
	//		m_numItems = numItems;
	//		m_items = new T[numItems];
	//	}

	//	~CappedStack()
	//	{
	//		delete[] m_items;
	//		m_items = 0;
	//	}

	//	T Add(T item)
	//	{
	//		if (m_top < m_numItems)
	//		{
	//			m_items[m_top++] = item;
	//		}
	//		else
	//		{
	//			// throw an exception
	//		}
	//	}

	//	int GetNumItems() {return m_numItems;}
	//	T operator[](int index) {return m_items[int];}
	//	
	//private:
	//	int m_numItems;
	//	int m_top;
	//	T* m_items;
	//};

	struct Position
	{
		int x;
		int y;
	};

	enum ObjectType
	{
		OBJ_TYPE_OBJECT = 0x0000, // either inanimate objects
		OBJ_TYPE_BLADE,
		OBJ_TYPE_CONTAINER,
		OBJ_TYPE_AGENT = 0x8000, // or living things
		OBJ_TYPE_PERSON,
		OBJ_TYPE_LAST = 0xffff
	};

	enum AttributeType
	{
		ATTRIB_TYPE_HEIGHT = 0x0000,
		ATTRIB_TYPE_WEIGHT,
		ATTRIB_TYPE_POSX,
		ATTRIB_TYPE_POSY,
		ATTRIB_TYPE_ALIVE,
		ATTRIB_TYPE_LAST = 0xffff
	};

	enum OperatorLayoutType
	{
		/*
		O for Object
		A for Attribute
		V for Value
		B indicates the boolean that can negate the result
		*/
		OP_LAYOUT_TYPE_OAVB,	// O has attrib A compared to V e.g. Dysh.height == 160
		OP_LAYOUT_TYPE_OOAB,	// O1 and O2 have attribute A compared e.g. Al.weight > Dysh.weight
		OP_LAYOUT_TYPE_OAOAB,	// O1 has attrib A1, O2 has attrib A2, compared e.g. Al.strength > Dysh.weight
		OP_LAYOUT_TYPE_OOB,		// O1 and O2 have object level relationship e.g. Al owns Knife
		OP_LAYOUT_TYPE_UNDEFINED = 0xffff
	};

	enum OperandSemanticType
	{
		OP_SEMANTIC_TYPE_INSTRUMENT = 0x0000,
		OP_SEMANTIC_TYPE_OBJECT,
		OP_SEMANTIC_UNDEFINED = 0xffff
	};

	enum OperatorType
	{
		OPER_TYPE_HAS_ATTIRB = 0x0000,
		
		OPER_TYPE_GREATER_THAN,
		OPER_TYPE_EQUAL,

		OPER_TYPE_PROXIMITY,

		OPER_TYPE_OWNS,

		OPER_TYPE_UNDEFINED = 0xffff
	};

	enum ActionType
	{
		ACTION_GOTO = 0x0000,
		ACTION_TAKE,
		ACTION_DROP,
		
		ACTION_CHOKE,
		ACTION_STAB
	};
}

#endif