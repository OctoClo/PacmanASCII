#pragma once

#define START_SCORE 0
#define SCORE_INCREMENT 100

#define CHAR_WALL '#'
#define CHAR_COLLECTIBLE '¤'

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

	void UpdateCollectible(int pEatenCollectibleX, int pEatenCollectibleY);
	ETile GetTileFromBoard(int pX, int pY);

	static LevelManager* GetInstance();

private:
	void FillBoard();
	void UpdateRendererOnce();
	void SpawnCollectible();
	void TileToChar(ETile& pTile, char& pAsciiChar, EColor& pForeground);

	int _score;
	ETile _board[SCREEN_HEIGHT][SCREEN_WIDTH];

	bool _firstGame;
	Coord _collectibleCoord;

	UiManager* _uiManager;
	Renderer* _renderer;

	static LevelManager* _instance;
};
