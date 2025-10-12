#ifndef _ACCUSER_H_
#define _ACCUSER_H_

#include "Agent.h"

namespace GOAP
{
	struct Roles
	{
		Agent* murderer = nullptr;
		Agent* victim = nullptr;
		Agent* thief = nullptr;
		Agent* witness = nullptr;
	};
}

class Accuser
{
public:
	Accuser();
	Accuser(const Accuser& other);
	~Accuser();

	GOAP::Agent* AccuseMurderer(const GOAP::Roles& roles, int murderer) const;

	GOAP::Agent* Prompt(const GOAP::Roles& roles) const;
	bool Submit(const GOAP::Roles& roles, const GOAP::Agent* allegedMurderer);
	int GetNumWitnesses(const GOAP::Roles& roles) const;

private:
	int m_numWitnesses;
};

#endif