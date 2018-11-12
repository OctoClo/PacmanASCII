#include "stdafx.h"
#include "Enums.h"
#include "Utils.h"

int Utils::Clamp(int pNumber, int pMin, int pMax) {
	return pNumber < pMin ? pMin : (pNumber > pMax ? pMax : pNumber);
}

//Receive a tile and update its visual in the editor
void Utils::TileToChar(ETile& pTile, char& pAsciiChar, EColor& pForeground)
{
	switch (pTile)
	{
	case ETile::Wall:
		pAsciiChar = CHAR_WALL;
		pForeground = EColor::Cyan;
		break;

	case ETile::Collectible:
		pAsciiChar = CHAR_COLLECTIBLE;
		pForeground = EColor::LightGreen;
		break;

	case ETile::SnakeHead:
		pAsciiChar = CHAR_SNAKE_HEAD;
		pForeground = EColor::LightYellow;
		break;

	case ETile::SnakeBody:
		pAsciiChar = CHAR_SNAKE_BODY;
		pForeground = EColor::Yellow;
		break;
	}


}