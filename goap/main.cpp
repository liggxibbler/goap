#include <iostream>
#include "Action.h"
#include "Game.h"
//#include <Windows.h>
#include <ctime>

using namespace std;
using namespace GOAP;

void MaximizeWindow();

int main()
{
	//seed = (unsigned int)time(nullptr);
	//srand(1386261647);

	MaximizeWindow();

	Action::OpenFile();

	Game game;
	
	Op::OperatorManager operatorManager;
	
	RoomManager roomManager;
	roomManager.Initialize();

	game.Initialize(roomManager);
	game.Run(operatorManager, roomManager);

	Action::CloseFile();

	return 0;
}

void MaximizeWindow()
{
	/*CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SMALL_RECT rc;
	rc.Left = 0;
	rc.Top = 0;
	rc.Right = (short)(min(info.dwMaximumWindowSize.X, info.dwSize.X) - 1);
	rc.Bottom = (short)(min(info.dwMaximumWindowSize.Y, info.dwSize.Y) - 1);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &rc);*/
	//ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}
