#include "Squeezer.h"

using namespace GOAP;

Squeezer::Squeezer() : STUFF()
{
}

Squeezer::Squeezer(std::string name) : STUFF(name)
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
	return OBJ_TYPE_SQUEEZER | OBJ_TYPE_OBJECT | OBJ_TYPE_STUFF;
}

bool Squeezer::CanBeMurderWeapon()
{
	return true;
}