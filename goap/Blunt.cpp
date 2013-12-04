#include "Blunt.h"

using namespace GOAP;

Blunt::Blunt() : Object()
{
}

Blunt::Blunt(std::string name) : Object(name)
{
}

Blunt::Blunt(const Blunt& other)
{
}

Blunt::~Blunt()
{
}

Blunt::operator GOAP::ObjectType()
{
	return OBJ_TYPE_BLUNT;
}

int Blunt::GetCompoundType()
{
	return OBJ_TYPE_BLUNT | OBJ_TYPE_OBJECT;
}

bool Blunt::CanBeMurderWeapon()
{
	return true;
}