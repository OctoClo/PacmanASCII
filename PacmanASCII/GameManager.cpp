
#include "stdafx.h"
#include "GameManager.h"

GameManager* GameManager::_instance = nullptr;

GameManager* GameManager::GetInstance() 
{
	if (!_instance) 
	{
		_instance = new GameManager();
	}

	return _instance;
}

void GameManager::GameLoop()
{
	Init();

	while (_gameState != EGameState::Quit)
	{
		ProcessInputs();
		Update();
		Render();
	}
}

void GameManager::Init()
{
	_renderer = Renderer::GetInstance();
	_renderer->Init();

	_levelManager = LevelManager::GetInstance();
	_levelManager->Init(_renderer);
	
	Start();
}

void GameManager::Start()
{
	_levelManager->Start();

	_gameState = EGameState::Play;
}

void GameManager::ProcessInputs()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 27) // Escape key
		{
			_gameState = EGameState::Quit;
		}

		_levelManager->ProcessInputs(key);
	}
}

void GameManager::Update()
{
	_levelManager->Update();
	_renderer->DrawChar(0, 0, '~', EColor::White);
}

void GameManager::Render()
{
	_levelManager->Render();
	_renderer->Render();
}