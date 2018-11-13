#pragma once

#define START_SCORE 0
#define SCORE_INCREMENT 100

#include "stdafx.h"
#include "Enums.h"
#include "Structs.h"
#include "Renderer.h"
#include "UiManager.h"
#include "Utils.h"

class LevelManager
{
public:
	void Init(Renderer* pRenderer);
	void Start();

	void UpdateCollectible(int pEatenCollectibleX, int pEatenCollectibleY, vector<SnakePiece> pSnake);
	void UpdateBuffer();
	ETile GetTileFromBoard(int pX, int pY);

	static LevelManager* GetInstance();

private:
	void FillBoard();
	void SpawnCollectible(vector<SnakePiece> pSnake = vector<SnakePiece>());
	bool IsPositionInSnake(int pX, int pY, vector<SnakePiece> pSnake);

	int _score;
	ETile _board[SCREEN_HEIGHT][SCREEN_WIDTH];

	bool _firstGame;
	Coord _collectibleCoord;

	UiManager* _uiManager;
	Renderer* _renderer;

	static LevelManager* _instance;
};
