
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
		UpdateRenderer();

		if (_gameState == EGameState::Play && Timer::CanMove())
		{
			int gameOver = (_snake->MoveSnake() != CORRECT_MOVE);
			
			if (gameOver)
			{
				_gameState = EGameState::Menu;
				_menuManager->LaunchEndMenu();
			}
		}

		Render();
	}
}

void GameManager::Init()
{
	_gameState = EGameState::Menu;

	_renderer = Renderer::GetInstance();
	_renderer->Init();

	_snake = new Snake();
	_snake->Init(_renderer);

	_levelManager = LevelManager::GetInstance();
	_levelManager->Init(_renderer);

	_menuManager = MenuManager::GetInstance();
	_menuManager->Init(_renderer);

	Timer::Start();
}

void GameManager::Start()
{
	_levelManager->Start();
	_snake->Start();

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
				switch (_menuManager->GetCurrentButton())
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
				(_menuManager->GetCurrentButton() == EButton::Quit ||
				_menuManager->GetCurrentMenu() == EMenuType::Begin))
			{
				_menuManager->SetCurrentButton(
					(_menuManager->GetCurrentMenu() == EMenuType::Begin) ?
					EButton::Start : EButton::Restart);
			}
			else if (_gameState == EGameState::Play)
			{
				_snake->UpdateDirection(EDirection::Up);
			}
			break;

		case KEY_Q: case KEY_Q_CAPITAL:
			if (_gameState == EGameState::Play)
			{
				_snake->UpdateDirection(EDirection::Left);
			}
			break;

		case KEY_S: case KEY_S_CAPITAL:
			if (_gameState == EGameState::Menu &&
				_menuManager->GetCurrentButton() != EButton::Quit)
			{
				_menuManager->SetCurrentButton(EButton::Quit);
			}
			else if (_gameState == EGameState::Play)
			{
				_snake->UpdateDirection(EDirection::Bottom);
			}
			break;

		case KEY_D: case KEY_D_CAPITAL:
			if (_gameState == EGameState::Play)
			{
				_snake->UpdateDirection(EDirection::Right);
			}
			break;
		}
	}
}

void GameManager::UpdateRenderer()
{
	switch (_gameState)
	{
	case EGameState::Menu:
		_menuManager->UpdateRenderer();
		break;

	case EGameState::Play:
		_snake->UpdateRenderer();
		break;
	}
}

void GameManager::Render()
{
	_renderer->Render();
}
