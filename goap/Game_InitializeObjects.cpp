#include "Common.h"
#include "Game.h"
#include "Prop.h"
#include "Blade.h"
#include "Blunt.h"
#include "Squeezer.h"
#include "Projectile.h"

using namespace GOAP;

void Game::InitializeObjects()
{
	/*
	clock
	scissors
	mirror
	bottle
	kettle
	toaster
	fork
	chemicals
	cups
	drinks
	foods
	*/

	m_objects.clear();
	Prop* obj = 0;

	//found in the living room:

	obj = new Blunt("Fireplace poker");
	obj->MayBeFoundIn(ROOM_LIVING_ROOM);
	obj->SetDescription("Poking the coal or wood fuel in the fireplace helps the fire breathe, poking someone in the heart has the exact opposite effect.");
	m_objects.push_back(obj);

	obj = new Prop("Umbrella Stand");
	obj->MayBeFoundIn(ROOM_LIVING_ROOM);
	obj->SetDescription("A cylindrical object holding umbrellas and walking sticks. Umbrella stands don't kill people; swords, clubs, and cane gun in the umbrella stands do.");
	m_objects.push_back(obj);

	obj = new Squeezer("Curtain Rope");
	obj->MayBeFoundIn(ROOM_LIVING_ROOM);
	obj->SetDescription("Used for holding the curtain on one side in the morning and strangling people on the other side in the afternoon.");
	m_objects.push_back(obj);

	obj = new Blunt("Globe");
	obj->MayBeFoundIn(ROOM_LIVING_ROOM);
	obj->SetDescription("A raised-relief globe in gold. i.e. a golden globe.");
	m_objects.push_back(obj);

	obj = new Blunt("Bust");
	obj->MayBeFoundIn(ROOM_LIVING_ROOM);
	obj->SetDescription("A bronze bust of Dysh the Great (one of the most unknown writers of the 18th century).");
	m_objects.push_back(obj);

	//found in the kitchen:

	obj = new Prop("Servant's Dining Table");
	obj->MayBeFoundIn(ROOM_KITCHEN);
	obj->SetDescription("Servant's dining table because they are too poor to use normal dining tables.");
	m_objects.push_back(obj);

	obj = new Blade("Chef's knife");
	obj->MayBeFoundIn(ROOM_KITCHEN);
	obj->SetDescription("A heavy duty knife used for cutting, chopping, and slicing bones and meat and people.");
	m_objects.push_back(obj);

	obj = new Blunt("Bottle of Wine");
	obj->MayBeFoundIn(ROOM_KITCHEN);
	obj->SetDescription("A vintage red wine bottle. It's so vintage and potent that even a shot glass of it can knock you out. The whole bottle will kill you... if bashed against your head.");
	m_objects.push_back(obj);

	//found in the dinning room:

	obj = new Blade("Cutlery Set");
	obj->MayBeFoundIn(ROOM_DINING_ROOM);
	obj->SetDescription("A set of silver cutlery. As your mom probably have mentioned, never run with a knife or a fork or both unless you want to accidentally stab someone in the heart.");
	m_objects.push_back(obj);

	obj = new Prop("Flower Pot");
	obj->MayBeFoundIn(ROOM_DINING_ROOM);
	obj->SetDescription("A big flower pot standing in the corner of the room looking pretty.");
	m_objects.push_back(obj);

	obj = new Squeezer("Curtain Rope");
	obj->MayBeFoundIn(ROOM_DINING_ROOM);
	obj->SetDescription("Used for holding the curtain on one side in the morning and strangling people in the afternoon.");
	m_objects.push_back(obj);

	//found in the bathroom:

	obj = new Prop("Scented Candle");
	obj->MayBeFoundIn(ROOM_BATHROOM);
	obj->SetDescription("A candle that emits scents. One might think it's useless but half of the earth's population may disagree.");
	m_objects.push_back(obj);

	obj = new Blade("Razor");
	obj->MayBeFoundIn(ROOM_BATHROOM);
	obj->SetDescription("An old straight razor (a.k.a cut-throat razor) used mainly for shaving and occasionally for cutting throats.");
	m_objects.push_back(obj);


		//obj = new Prop("Clock");
		//obj->MayBeFoundIn(ROOM_BATHROOM | ROOM_BEDROOM | ROOM_LIVING_ROOM | ROOM_DINING_ROOM);
		//obj->SetDescription("DESCRIPTION");
		//m_objects.push_back(obj);

		//obj = new Prop("Cup");
		//obj->MayBeFoundIn(ROOM_KITCHEN | ROOM_DINING_ROOM);
		//obj->SetDescription("DESCRIPTION");
		//m_objects.push_back(obj);

		//obj = new Blade("Knife");
		//obj->MayBeFoundIn(ROOM_KITCHEN | ROOM_DINING_ROOM);
		//obj->SetDescription("DESCRIPTION");
		//m_objects.push_back(obj);

		//obj = new Squeezer("Rope");
		//obj->MayBeFoundIn(ROOM_KITCHEN);
		//obj->SetDescription("DESCRIPTION");
		//m_objects.push_back(obj);

		//obj = new Blunt("Statue");
		//obj->MayBeFoundIn(ROOM_LIVING_ROOM | ROOM_BEDROOM);
		//obj->SetDescription("DESCRIPTION");
		//m_objects.push_back(obj);

		//obj = new Prop("Lamp");
		//obj->MayBeFoundIn(ROOM_BATHROOM | ROOM_BEDROOM | ROOM_LIVING_ROOM | ROOM_DINING_ROOM);
		//obj->SetDescription("DESCRIPTION");
		//m_objects.push_back(obj);

		//obj = new Prop("Table");
		//obj->MayBeFoundIn(ROOM_KITCHEN | ROOM_DINING_ROOM | ROOM_LIVING_ROOM);
		//obj->SetDescription("DESCRIPTION");
		//m_objects.push_back(obj);

		//obj = new Projectile("Gun");
		//obj->MayBeFoundIn(ROOM_BEDROOM);
		//obj->SetDescription("DESCRIPTION");
		//m_objects.push_back(obj);
}