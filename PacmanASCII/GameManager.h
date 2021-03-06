#pragma once

#define KEY_ESC 27
#define KEY_ENTER 13

#define KEY_UP 72
#define KEY_Z 122
#define KEY_Z_CAPITAL 90

#define KEY_LEFT 75
#define KEY_Q 113
#define KEY_Q_CAPITAL 81

#define KEY_DOWN 80
#define KEY_S 115
#define KEY_S_CAPITAL 83

#define KEY_RIGHT 77
#define KEY_D 100
#define KEY_D_CAPITAL 68

#include "stdafx.h"
#include "Enums.h"
#include "Renderer.h"
#include "Snake.h"
#include "LevelManager.h"
#include "MenuManager.h"
#include "UiManager.h"
#include "Timer.h"

class GameManager
{
public:
	void GameLoop();

	static GameManager* GetInstance();

private:
	void Init();
	void Start();

	void ProcessInputs();
	void UpdateBuffer();
	void Render();

	void ProcessEnterInput();
	void ProcessUpInput();
	void ProcessLeftInput();
	void ProcessDownInput();
	void ProcessRightInput();

	EGameState _gameState;

	Snake* _snake;
	LevelManager* _levelManager;
	MenuManager* _menuManager;
	Renderer* _renderer;

	static GameManager* _instance;
};