// PacmanASCII.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "GameManager.h"

#define WIN32_LEAN_AND_MEAN
#define SCREEN_WIDTH 250
#define SCREEN_HEIGHT 500

using namespace std;

int main()
{
	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

	// Hide blinking caret
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hOutput, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOutput, &cursorInfo);

	ReadConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);

	buffer[5][10].Char.AsciiChar = 'H';
	buffer[5][10].Attributes = 0x0E;
	buffer[5][11].Char.AsciiChar = 'i';
	buffer[5][11].Attributes = 0x0B;
	buffer[5][12].Char.AsciiChar = '!';
	buffer[5][12].Attributes = 0x0A;

	WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);

	GameManager* gm = GameManager::GetInstance();

	while (1)
	{
		if (_kbhit())
		{
			break;
		}
	}

	return 0;
}

