#include "Projectile.h"

using namespace GOAP;

Projectile::Projectile() : STUFF()
{
}

Projectile::Projectile(std::string name) : STUFF(name)
{
}

Projectile::Projectile(const Projectile& other)
{
}

Projectile::~Projectile()
{
}

Projectile::operator GOAP::ObjectType()
{
	return OBJ_TYPE_PROJECTILE;
}

int Projectile::GetCompoundType()
{
	return OBJ_TYPE_PROJECTILE | OBJ_TYPE_OBJECT;
}

bool Projectile::CanBeMurderWeapon()
{
	return true;
}