#ifndef _GOAP_DIGIT_H_
#define _GOAP_DIGIT_H_

namespace GOAP
{
	class Digit
	{
	public:

		Digit(int size, Digit* higher) :
		  m_size(size), m_higher(higher)
		{
			m_pointer = 0;
		}

		bool Increase()
		{
			++m_pointer %= m_size;
			if (m_pointer == 0)
			{
				if(m_higher == NULL)
				{
					return false;
				}
				else
				{
					m_higher->Increase();
					return true;
				}
			}
		}

		int GetPointer()
		{
			return m_pointer;
		}

	private:
		int m_size;
		int m_pointer;
		Digit* m_higher;
	};
}

#endif