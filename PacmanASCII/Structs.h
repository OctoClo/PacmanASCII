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
	// Coord
	int x, y;
	ETile pieceType;

	SnakePiece(int pX = 0, int pY = 0, ETile pPieceType = ETile::SnakeBody)
	{
		x = pX;
		y = pY;
		pieceType = pPieceType;
	}
};