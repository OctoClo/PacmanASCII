#pragma once

#define START_SCORE 0
#define MAX_LIVES 3

#define START_SNAKE_HEAD_X 12
#define START_SNAKE_HEAD_Y 80
#define START_SNAKE_SIZE 3

#define INCORRECT_MOVE 0
#define CORRECT_MOVE 1

#include "stdafx.h"
#include "Enums.h"
#include "Renderer.h"

struct SnakePiece
{
	int x, y;
	ETile pieceType;

	SnakePiece(int pX = 0, int pY = 0, ETile pPieceType = ETile::SnakeBody)
	{
		x = pX;
		y = pY;
		pieceType = pPieceType;
	}
};

class LevelManager
{
public:
	void Init(Renderer* pRenderer);
	void Start();

	void Update();
	void Render();

	int MoveSnake(int pDirX, int pDirY);

	static LevelManager* GetInstance();

private:
	void RenderBoard();
	void CreateSnake();
	void FillBoard();
	void SpawnCollectible();
	void CleanLastTile(int pLastIndex);
	int CheckCollisions();
	void TileToChar(ETile& pTile, char& pAsciiChar, EColor& pForeground);

	int _score;
	int _lives;
	ETile _board[SCREEN_HEIGHT][SCREEN_WIDTH];

	vector<SnakePiece> _snake;

	Renderer* _renderer;

	static LevelManager* _instance;
};
