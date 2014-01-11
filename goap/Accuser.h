#ifndef _ACCUSER_H_
#define _ACCUSER_H_

#include "Agent.h"

class Accuser
{
public:
	Accuser();
	Accuser(const Accuser& other);
	~Accuser();

	void Initialize(GOAP::Agent* murderer, GOAP::Agent* thief, GOAP::Agent* witness);
	void AccuseThief(int thief);
	void AccuseMurderer(int murderer);

	bool Prompt(); 

	bool Submit();

private:

	GOAP::Agent* m_murderer;
	GOAP::Agent* m_thief;
	GOAP::Agent* m_witness;

	GOAP::Agent* m_allegedMurderer;
	GOAP::Agent* m_allegedThief;

	int m_numWitnesses;
};

#endif