#include "Accuser.h"

Accuser::Accuser()
{
}

Accuser::Accuser(const Accuser& other)
{
}

Accuser::~Accuser()
{
}

int Accuser::GetNumWitnesses(const GOAP::Roles& roles) const
{
	return roles.witness ? 3 : 2;
}

bool Accuser::Submit(const GOAP::Roles& roles, const GOAP::Agent* allegedMurderer)
{
	return allegedMurderer == roles.murderer;
}

GOAP::Agent* Accuser::Prompt(const GOAP::Roles& roles) const
{
	while(true)
	{
		system("cls");
		
		int murdererIndex = -1;
		GOAP::Agent* allegedMurderer = nullptr;
		while(murdererIndex < 1 || murdererIndex > GetNumWitnesses(roles))
		{
			std::cout << "===============================================\n\n";
			std::cout << "Who do you think was the murderer?\n\n";
			std::cout << "1. " << roles.thief->GetName() << "\n\n";
			std::cout << "2. " << roles.murderer->GetName() << "\n\n";
			if(roles.witness != nullptr)
			{
				std::cout << "3. " << roles.witness->GetName() << "\n\n";
			}
			std::cout << "0. Go back to Constable Sauce\n\n";
			
			std::cout << ">>> ";

			std::cin >> murdererIndex;
			
			if(murdererIndex == 0)
			{
				return nullptr;
			}

			allegedMurderer = AccuseMurderer(roles, murdererIndex - 1);
		}

		std::cout << "\nSo you think that " << allegedMurderer->GetName() << " was the killer? (Y/N)\n\n";
		std::cout << ">>> ";
		char answer;
		std::cin >> answer;
		if ((answer == 'y') || (answer == 'Y'))
		{
			return allegedMurderer;
		}
		else
		{
			return nullptr;
		}
	}
}

GOAP::Agent* Accuser::AccuseMurderer(const GOAP::Roles& roles, int murderer) const
{
	switch(murderer)
	{
	case 0:
		return roles.thief;
	case 1:
		return roles.murderer;
	case 2:
		return roles.witness;
	default:
		return nullptr;
	}
}