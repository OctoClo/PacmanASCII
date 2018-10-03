// PacmanASCII.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "GameManager.h"
#include <algorithm>

#define WIN32_LEAN_AND_MEAN
#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 25

using namespace std;

CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

int x = 0;
int y = 0;

enum Color {
	Transparent,
	Blue,
	Green,
	Cyan,
	Red,
	Purple,
	Yellow,
	White,
	Grey,
	LightBlue,
	LightGreen,
	LightCyan,
	LightRed,
	LightPurple,
	LightYellow,
	LightWhite,
	LightGrey
};
static int GetASCIIColor(Color pForeground, Color pBackground)
{
	int output(0);
	output = pForeground + (pBackground * 16);
	return output;
}

void CleanPreviousTile() {
	buffer[x][y].Char.AsciiChar = 'H';
	buffer[x][y].Attributes = GetASCIIColor(Color::Transparent, Color::Transparent);
}

void UpdateTiles(int pX=0, int pY=0) {
	
	//As -- = + we should invert the tests
	if ((x + pX) < 0 || (x + pX) > SCREEN_HEIGHT - 1) pX = 0;
	if ((y + pY) < 0 || (y + pY) > SCREEN_WIDTH - 1) pY = 0;

	buffer[x + pX][y + pY].Char.AsciiChar = 'H';
	buffer[x + pX][y + pY].Attributes = GetASCIIColor(Color::LightYellow, Color::Transparent);

	x += pX;
	y += pY;
}

int main()
{
	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	//CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

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
		int key = 0;

		if (_kbhit())
		{
			key = _getch();

			switch (key) {
			case 'z':
				CleanPreviousTile();
				UpdateTiles(-1,0);

				WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

				break;

			case 's':
				CleanPreviousTile();
				UpdateTiles(1, 0);

				WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

				break;

			case 'q':
				CleanPreviousTile();
				UpdateTiles(0, -1);

				WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

				break;

			case 'd':
				CleanPreviousTile();
				UpdateTiles(0, 1);

				WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

				break;

			default:
				break;
			}
		}
		/*if (_kbhit())
		{
			break;
		}*/
	}


	return 0;
}

