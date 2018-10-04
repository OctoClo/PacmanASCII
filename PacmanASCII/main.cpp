// PacmanASCII.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "GameManager.h"
#include <algorithm>
#include <map>
#include <string>
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 25

using namespace std;

CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

struct Coords {
	int x, y;

	Coords(int pX = 0, int pY = 0) {
		x = pX;
		y = pY;
	}
};

std::map<int, Coords> snakeMap;

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

//Keep the last tile where the snake was, and clean it
void CleanPreviousTile() {
	
	int lastIndex;

	//Security, in case the map is empty
	if (snakeMap.size() - 1 < 0) lastIndex = 0;
	else lastIndex = snakeMap.size() - 1;

	Coords previousCoord = snakeMap[lastIndex];

	buffer[previousCoord.x][previousCoord.y].Char.AsciiChar = 'H';
	buffer[previousCoord.x][previousCoord.y].Attributes = GetASCIIColor(Color::Transparent, Color::Transparent);
}

//Update the buffer to make the snake moving
void UpdateTiles(int pX=0, int pY=0) 
{
	int length = snakeMap.size() - 1;

	for (int i = length; i >= 0; i--) 
	{
		if (i == length) CleanPreviousTile();

		if (i == 0) {
			Coords snakeHeadCoord = snakeMap[0];

			//Block the snake from moving outside the boards
			//As -- = + we should invert the tests
			if ((snakeHeadCoord.x + pX) < 0 || (snakeHeadCoord.x + pX) > SCREEN_HEIGHT - 1) pX = 0;
			if ((snakeHeadCoord.y + pY) < 0 || (snakeHeadCoord.y + pY) > SCREEN_WIDTH - 1) pY = 0;

			Coords newSnakeHeadCoord(snakeHeadCoord.x + pX, snakeHeadCoord.y + pY);

			snakeMap[0] = newSnakeHeadCoord;

			buffer[newSnakeHeadCoord.x][newSnakeHeadCoord.y].Char.AsciiChar = 'H';
			buffer[newSnakeHeadCoord.x][newSnakeHeadCoord.y].Attributes = GetASCIIColor(Color::LightYellow, Color::Transparent);

			break;
		}

		snakeMap[i] = snakeMap[i-1];
		Coords newCoord = snakeMap[i];

		buffer[newCoord.x][newCoord.y].Char.AsciiChar = '-';
		buffer[newCoord.x][newCoord.y].Attributes = GetASCIIColor(Color::LightBlue, Color::Transparent);
	}
}

int main()
{
#pragma region Test Buffer

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

	/*buffer[5][10].Char.AsciiChar = 'H';
	buffer[5][10].Attributes = 0x0E;
	buffer[5][11].Char.AsciiChar = 'i';
	buffer[5][11].Attributes = 0x0B;
	buffer[5][12].Char.AsciiChar = '!';
	buffer[5][12].Attributes = 0x0A;*/

	//WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

	GameManager* gm = GameManager::GetInstance();
#pragma endregion

	Coords firstCoords(10, 10);
	Coords secondCoords(10, 11);
	Coords thirdCoords(10, 12);

	snakeMap.insert(std::make_pair(0, firstCoords));
	snakeMap.insert(std::make_pair(1, secondCoords));
	snakeMap.insert(std::make_pair(2, thirdCoords));

	//A LA DURE
	buffer[10][10].Char.AsciiChar = 'H';
	buffer[10][10].Attributes = 0x0E;
	buffer[10][11].Char.AsciiChar = '-';
	buffer[10][11].Attributes = 0x0B;
	buffer[10][12].Char.AsciiChar = '-';
	buffer[10][12].Attributes = 0x0B;

	WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

	//int test = snakeMap[0].x;
	//snakeMap[0] = firstCoords;
	

	while (1)
	{
		int key = 0;

		if (_kbhit())
		{
			key = _getch();

			switch (key) {
			case 'z':
				UpdateTiles(-1,0);

				WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

				break;

			case 's':
				UpdateTiles(1, 0);

				WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

				break;

			case 'q':
				UpdateTiles(0, -1);

				WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

				break;

			case 'd':
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

