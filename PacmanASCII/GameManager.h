#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#pragma once

#include "stdafx.h"
#include "Renderer.h"
#include "LevelManager.h"

enum EGameState
{
	Play,
	Menu,
	Quit
};

class GameManager
{
public:
	void GameLoop();

	static GameManager* GetInstance();

private:
	void Init();
	void Start();

	void ProcessInputs();
	void Update();
	void Render();

	EGameState _gameState;

	LevelManager* _levelManager;
	Renderer* _renderer;

	static GameManager* _instance;
};
#endif