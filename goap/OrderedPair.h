#ifndef _GOAP_ORDEREDPAIR_H_
#define _GOAP_ORDEREDPAIR_H_

#include "Counter.h"
#include <vector>

namespace GOAP
{
	template <class T>
	class OrderedPair
	{
	public:
		OrderedPair()
		{
			m_Counters = NULL;
		}

		~OrderedPair()
		{
			delete[] m_Counters;
		}

		typename std::vector<T> GetNextOrderedPair(bool& status)
		{
			static std::vector<T> result;
			result.clear();

			if(m_Counters[0]->GetOverflow())
			{
				status = true;
			}
			else
			{
				result = GenerateOrderedPair();
				m_Counters[numLists - 1]->Increase();
				status = false;
			}
			return result;
		}

		bool Initialize(typename std::vector< std::vector<T> > lists, int _numLists)
		{
			m_lists = lists;
			numLists = _numLists;

			m_Counters = new Counter*[numLists];
			Counter* higher = NULL;
			for(int i=0; i<numLists; i++)
			{
				m_Counters[i] = new Counter( m_lists[i].size(), higher); // XIBB test for failed new
				higher = m_Counters[i];
			}

			return true;
		}

		bool Clear()
		{
			typename std::vector<std::vector<T> >::iterator iter;
			for(iter = m_lists.begin(); iter != m_lists.end(); ++iter)
			{
				(*iter).clear();
			}
			m_lists.clear();
			
			return true;
		}
	
	private:
		typename std::vector<T> GenerateOrderedPair()
		{
			m_result.clear();
			for(unsigned int i=0; i < m_lists.size(); i++)
			{
				typename std::vector<T> list = m_lists.at(i);
				m_result.push_back( list.at(m_Counters[i]->GetPointer()) );
			}
			return m_result;
		}

	private:
		int numLists;
		Counter** m_Counters;
		typename std::vector< std::vector<T> > m_lists;
		typename std::vector<T> m_result;
	};
}
#endif