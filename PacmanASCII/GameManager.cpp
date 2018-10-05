
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

	while (_gameState != EGameState::Exit)
	{
		ProcessInputs();
		Update();
		Render();
	}
}

void GameManager::Init()
{
	_gameState = EGameState::Menu;

	_renderer = Renderer::GetInstance();
	_renderer->Init();

	_levelManager = LevelManager::GetInstance();
	_levelManager->Init(_renderer);

	_uiManager = UiManager::GetInstance();
	_uiManager->Init(_renderer);
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

		if (key == KEY_ESC)
		{
			_gameState = EGameState::Exit;
		}

		switch (key)
		{
		case KEY_ENTER:
			if (_gameState == EGameState::Menu)
			{
				switch (_uiManager->GetCurrentButton())
				{
				case EButton::Start: case EButton::Restart:
					_renderer->ClearScreen();
					Start();
					break;

				case EButton::Quit:
					_gameState = EGameState::Exit;
					break;
				}
			}
			break;

		case KEY_Z: case KEY_Z_CAPITAL:
			if (_gameState == EGameState::Menu &&
				_uiManager->GetCurrentButton() == EButton::Quit &&
				_uiManager->GetCurrentMenu() == EMenuType::Begin)
			{
				_uiManager->SetCurrentButton(
					(_uiManager->GetCurrentMenu() == EMenuType::Begin) ?
					EButton::Start : EButton::Restart);
			}
			else if (_gameState == EGameState::Play)
			{
				if (_levelManager->MoveSnake(-1, 0) != CORRECT_MOVE)
				{
					_gameState = EGameState::Menu;
					_uiManager->LaunchEndMenu();
				}
			}
			break;

		case KEY_Q: case KEY_Q_CAPITAL:
			if (_gameState == EGameState::Play)
			{
				if (_levelManager->MoveSnake(0, -1) != CORRECT_MOVE)
				{
					_gameState = EGameState::Menu;
					_uiManager->LaunchEndMenu();
				}
			}
			break;

		case KEY_S: case KEY_S_CAPITAL:
			if (_gameState == EGameState::Menu &&
				_uiManager->GetCurrentButton() != EButton::Quit)
			{
				_uiManager->SetCurrentButton(EButton::Quit);
			}
			else if (_gameState == EGameState::Play)
			{
				if (_levelManager->MoveSnake(1, 0) != CORRECT_MOVE)
				{
					_gameState = EGameState::Menu;
					_uiManager->LaunchEndMenu();
				}
			}
			break;

		case KEY_D: case KEY_D_CAPITAL:
			//TEST
			/*if (_gameState == EGameState::Play)
			{
				_levelManager->UpdateSnake();
			}*/
			break;
			if (_gameState == EGameState::Play)
			{
				if (_levelManager->MoveSnake(0, 1) != CORRECT_MOVE)
				{
					_gameState = EGameState::Menu;
					_uiManager->LaunchEndMenu();
				}
			}
			break;
		}
	}
}

void GameManager::Update()
{
	if (_gameState == EGameState::Play)
		_levelManager->Update();
}

void GameManager::Render()
{
	switch (_gameState)
	{
	case EGameState::Menu:
		_uiManager->Render();
		break;

	case EGameState::Play:
		_levelManager->Render();
		break;
	}

	_renderer->Render();
}