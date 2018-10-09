#pragma once

#define START_SCORE 0
#define SCORE_INCREMENT 100

#define START_SNAKE_HEAD_X 12
#define START_SNAKE_HEAD_Y 80
#define START_SNAKE_SIZE 3

#define INCORRECT_MOVE 0
#define CORRECT_MOVE 1

#define CHAR_WALL '#'
#define CHAR_SNAKE_HEAD '@'
#define CHAR_SNAKE_BODY 'o'
#define CHAR_COLLECTIBLE '�'

#include "stdafx.h"
#include "Enums.h"
#include "Renderer.h"
#include "UiManager.h"

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

	void UpdateRenderer();

	int MoveSnake(int pDirX, int pDirY);

	static LevelManager* GetInstance();

private:
	void RenderBoard();
	void CreateSnake();
	void FillBoard();
	void SpawnCollectible();
	void CleanLastTile(int pLastIndex);
	int CheckCollisions(int pDirX, int pDirY);
	void TileToChar(ETile& pTile, char& pAsciiChar, EColor& pForeground);

	int _score;
	ETile _board[SCREEN_HEIGHT][SCREEN_WIDTH];

	vector<SnakePiece> _snake;

	UiManager* _uiManager;
	Renderer* _renderer;

	static LevelManager* _instance;
};
