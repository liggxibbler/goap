#include "Squeezer.h"

using namespace GOAP;

int Squeezer::s_value = 0;
int Squeezer::s_numInstances = 0;

Squeezer::Squeezer() : Prop()
{
	++s_numInstances;
}

Squeezer::Squeezer(std::string name) : Prop(name)
{
	++s_numInstances;
}

Squeezer::Squeezer(const Squeezer& other)
{
}

Squeezer::~Squeezer()
{
}

//Squeezer::operator GOAP::ObjectType()
//{
//	return OBJ_TYPE_SQUEEZER;
//}

int Squeezer::GetCompoundType()
{
	return OBJ_TYPE_SQUEEZER | OBJ_TYPE_OBJECT | OBJ_TYPE_PROP;
}

bool Squeezer::CanBeMurderWeapon()
{
	return true;
}

void Squeezer::IncreaseValue()
{
	s_value += 100;
}

int Squeezer::GetValue()
{
	return s_value;
}

int Squeezer::GetNumberOfInstances()
{
	return s_numInstances;
}