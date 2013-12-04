#include "Squeezer.h"

using namespace GOAP;

Squeezer::Squeezer() : Object()
{
}

Squeezer::Squeezer(std::string name) : Object(name)
{
}

Squeezer::Squeezer(const Squeezer& other)
{
}

Squeezer::~Squeezer()
{
}

Squeezer::operator GOAP::ObjectType()
{
	return OBJ_TYPE_SQUEEZER;
}

int Squeezer::GetCompoundType()
{
	return OBJ_TYPE_SQUEEZER | OBJ_TYPE_OBJECT;
}

bool Squeezer::CanBeMurderWeapon()
{
	return true;
}