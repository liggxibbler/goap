#ifndef _GOAP_COMBINATION_H_
#define _GOAP_COMBINATION_H_

#include "Digit.h"
#include <vector>

namespace GOAP
{
	template <class T>
	class Combination
	{
	public:
		Combination(typename std::vector< std::vector<T> > lists, int _numLists):
		  m_lists (lists), numLists(_numLists)
		  {		
			  m_Counters = new Counter*[numLists];
			  Counter* higher = NULL;
			  for(int i=0; i<numLists; i++)
			  {
				  m_Counters[i] = new Counter( m_lists[i].size(), higher);
				  higher = m_Counters[i];
			  }
		  }

		  ~Combination()
		  {
			  delete[] m_Counters;
		  }

		  typename std::vector<T> GetNextCombination(bool& status)
		  {
			  static std::vector<T> result;
			  result.clear();

			  if(m_Counters[0]->GetOverflow())
			  {
				  status = true;
			  }
			  else
			  {
				  result = GenerateCombination();
				  m_Counters[numLists - 1]->Increase();
				  status = false;
			  }
			  return result;
		  }

		  typename std::vector<T> GenerateCombination()
		  {
			  m_result.clear();
			  for(unsigned int i=0; i < m_lists.size(); i++)
			  {
				  typename std::vector<T> list = m_lists.at(i);
				  m_result.push_back( list.at(m_Counters[i]->GetPointer()) );
			  }
			  return m_result;
		  }

		  bool Initialize();

	private:
		int m_numLists;
		Counter** m_Counters;
		typename std::vector< std::vector<T> > m_lists;
		typename std::vector<T> m_result;
	};

#endif