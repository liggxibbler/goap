#include "Accuser.h"

Accuser::Accuser() : m_murderer(0), m_thief(0), m_witness(0), m_allegedMurderer(0), m_allegedThief(0)
{
}

Accuser::Accuser(const Accuser& other)
{
}

Accuser::~Accuser()
{
}

void Accuser::Initialize(GOAP::Agent* murderer, GOAP::Agent* thief, GOAP::Agent* witness)
{
	m_murderer = murderer;
	m_thief = thief;
	m_witness = witness;
}

bool Accuser::Submit()
{
	if ( m_allegedMurderer == m_murderer && m_allegedThief == m_thief)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Accuser::Prompt()
{
	while(true)
	{
		system("cls");
		
		int murderer = -1;
		while(murderer < 1 || murderer > 3)
		{
			std::cout << "===============================================\n\n";
			std::cout << "Who do you think was the murderer?\n\n";
			std::cout << "1. " << m_thief->GetName() << "\n\n";
			std::cout << "2. " << m_murderer->GetName() << "\n\n";
			std::cout << "3. " << m_witness->GetName() << "\n\n";
			std::cout << "0. Go back to Constable Sauce\n\n";
			std::cout << ">>> ";

			std::cin >> murderer;
			
			if(murderer == 0)
			{
				return false;
			}

			AccuseMurderer(murderer - 1);
		}

		int thief = -1;

		while(thief < 1 || thief > 3)
		{
			std::cout << "===============================================\n\n";
			std::cout << "Who do you think was the thief?\n\n";
			std::cout << "1. " << m_murderer->GetName() << "\n\n";
			std::cout << "2. " << m_witness->GetName() << "\n\n";
			std::cout << "3. " << m_thief->GetName() << "\n\n";
			std::cout << "0. Go back to Constable Sauce\n\n";
			std::cout << ">>> ";

			std::cin >> thief;

			if(thief == 0)
			{
				return false;
			}

			AccuseThief(thief - 1);
		}

		std::cout << "So you think that " << m_allegedMurderer->GetName() << " was the killer,\n\n";
		std::cout << "And " << m_allegedThief->GetName() << " was the thief?\n\n";
		std::cout << "(Y/N) >>> ";
		char answer;
		std::cin >> answer;
		if ((answer == 'y') || (answer == 'Y'))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void Accuser::AccuseMurderer(int murderer)
{
	switch(murderer)
	{
	case 0:
		m_allegedMurderer = m_thief;
		break;
	case 1:
		m_allegedMurderer= m_murderer;
		break;
	case 2:
		m_allegedMurderer = m_witness;
		break;
	default:
		// WRONG
		break;
	}
}

void Accuser::AccuseThief(int thief)
{
	switch(thief)
	{
	case 0:
		m_allegedThief = m_murderer;
		break;
	case 1:
		m_allegedThief = m_witness;
		break;
	case 2:
		m_allegedThief= m_thief;
		break;
	default:
		// WRONG
		break;
	}
}