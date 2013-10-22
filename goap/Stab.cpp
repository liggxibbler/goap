#include "Stab.h"

using namespace GOAP;

Stab::Stab(Agent* subject, Agent* victim, Object* blade)
{
}

Stab::Stab()
{
	m_args[OP_SEMANTIC_TYPE_SUBJECT] = NULL;
	m_args[OP_SEMANTIC_TYPE_OBJECT] = NULL;
	m_args[OP_SEMANTIC_TYPE_INSTRUMENT] = NULL;
}

Stab::Stab(const Stab& other)
{
}

Stab::~Stab()
{
}

void Stab::Execute()
{
}

Stab::operator ActionType()
{
	return ACTION_STAB;
}

Stab* Stab::Clone()
{
	Stab* newStab = new Stab();
	return newStab;
}