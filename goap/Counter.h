#ifndef _GOAP_COUNTER_H_
#define _GOAP_COUNTER_H_

namespace GOAP
{
	class Counter
	{
	public:
		Counter(int size, Counter* higher);
		bool Increase();
		int GetPointer();
		bool GetOverflow();

	private:
		int m_size;
		int m_pointer;
		Counter* m_higher;
		bool m_overflow;
	};
}

#endif