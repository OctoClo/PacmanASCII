#pragma once

#define START_SNAKE_HEAD_X 12
#define START_SNAKE_HEAD_Y 80
#define START_SNAKE_SIZE 3

#define INCORRECT_MOVE 0
#define CORRECT_MOVE 1

#include "stdafx.h"
#include "Enums.h"
#include "Structs.h"
#include "Renderer.h"
#include "LevelManager.h"

class Snake
{
public:
	void Init(Renderer* pRenderer);
	void Start();

	void UpdateBuffer();
	void UpdateDirection(EDirection pDirection);

	int MoveSnake();
	void EnlargeSnake();

	static Snake* GetInstance();

private:
	void InitDirectionCoordMap();
	void CreateSnake();
	int CheckCollisions();
	void CleanLastTile(int pLastIndex);

	EDirection _currentDir;
	map<EDirection, Coord> _directionsCoordMap;

	vector<SnakePiece> _snake;

	Renderer* _renderer;

	static Snake* _instance;
};