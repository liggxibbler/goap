#include "Blunt.h"

using namespace GOAP;

Blunt::Blunt() : STUFF()
{
}

Blunt::Blunt(std::string name) : STUFF(name)
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
	return OBJ_TYPE_BLUNT | OBJ_TYPE_OBJECT | OBJ_TYPE_STUFF;
}

bool Blunt::CanBeMurderWeapon()
{
	return true;
}