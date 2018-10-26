#pragma once

struct Coord
{
	int x, y;

	Coord(int pX = 0, int pY = 0)
	{
		x = pX;
		y = pY;
	}
};

struct SnakePiece
{
	Coord coord;
	ETile pieceType;

	SnakePiece(int pX = 0, int pY = 0, ETile pPieceType = ETile::SnakeBody)
	{
		coord = Coord(pX, pY);
		pieceType = pPieceType;
	}
};