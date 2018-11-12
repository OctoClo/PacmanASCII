#pragma once

#define CHAR_WALL '#'
#define CHAR_COLLECTIBLE '¤'
#define CHAR_SNAKE_HEAD '@'
#define CHAR_SNAKE_BODY 'o'

class Utils 
{
public:
	static int Clamp(int pNumber, int pMin, int pMax);
	static void TileToChar(ETile& pTile, char& pAsciiChar, EColor& pForeground);
};
