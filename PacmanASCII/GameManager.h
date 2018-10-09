#pragma once

#define KEY_ESC 27
#define KEY_ENTER 13

#define KEY_Z 122
#define KEY_Z_CAPITAL 90

#define KEY_Q 113
#define KEY_Q_CAPITAL 81

#define KEY_S 115
#define KEY_S_CAPITAL 83

#define KEY_D 100
#define KEY_D_CAPITAL 68

#include "stdafx.h"
#include "Enums.h"
#include "Renderer.h"
#include "LevelManager.h"
#include "MenuManager.h"
#include "UiManager.h"

class GameManager
{
public:
	void GameLoop();

	static GameManager* GetInstance();

private:
	void Init();
	void Start();

	void ProcessInputs();
	void UpdateRenderer();
	void Render();

	EGameState _gameState;

	LevelManager* _levelManager;
	MenuManager* _menuManager;
	Renderer* _renderer;

	static GameManager* _instance;
};