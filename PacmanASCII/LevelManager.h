#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#pragma once

#define START_SCORE 0
#define MAX_LIVES 3
#define START_SNAKE_HEAD_X 12
#define START_SNAKE_HEAD_Y 80
#define START_SNAKE_SIZE 3

#include "stdafx.h"
#include "Renderer.h"

enum ETile
{
	Nothing,
	Wall,
	SnakeHead,
	SnakeBody,
	Collectible
};

class LevelManager
{
public:
	void Init(Renderer* pRenderer);
	void Start();

	void ProcessInputs(int pKey);
	void Update();
	void Render();

	static LevelManager* GetInstance();

private:
	void CreateLevel();
	void SpawnCollectible();
	void TileToChar(ETile& pTile, char& asciiChar, EColor& pForeground);

	int _score;
	int _lives;
	unsigned int _snakeHeadX, _snakeHeadY;
	ETile _board[SCREEN_HEIGHT][SCREEN_WIDTH];

	Renderer* _renderer;

	static LevelManager* _instance;
};

#endif
