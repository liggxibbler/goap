#define NULL 0
#include "Counter.h"

using namespace GOAP;

Counter::Counter(int size, Counter* higher) :
m_size(size), m_higher(higher)
{
	m_pointer = 0;
	m_overflow = false;
}

bool Counter::Increase()
{
	++m_pointer %= m_size;
	if (m_pointer == 0)
	{
		if(m_higher == NULL)
		{
			m_overflow = true;
			return false;
		}
		else
		{
			m_higher->Increase();
			return true;
		}
	}
	else
	{
		return true;
	}

}

int Counter::GetPointer()
{
	return m_pointer;
}

bool Counter::GetOverflow()
{
	return m_overflow;
}