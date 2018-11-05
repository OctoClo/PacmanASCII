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

		// Move snake only if we're playing and timer says so
		if (_gameState == EGameState::Play && Timer::CanMove())
		{
			// Game over happens if snake does an incorrect move
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
		else
		{
			switch (key)
			{
			case KEY_ENTER:
				ProcessEnterInput();
				break;

			case KEY_UP: case KEY_Z: case KEY_Z_CAPITAL:
				ProcessUpInput();
				break;

			case KEY_LEFT: case KEY_Q: case KEY_Q_CAPITAL:
				ProcessLeftInput();
				break;

			case KEY_DOWN: case KEY_S: case KEY_S_CAPITAL:
				ProcessDownInput();
				break;

			case KEY_RIGHT: case KEY_D: case KEY_D_CAPITAL:
				ProcessRightInput();
				break;
			}
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

void GameManager::ProcessEnterInput()
{
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
}

void GameManager::ProcessUpInput()
{
	// If we're in menu and current button is Quit
	if (_gameState == EGameState::Menu &&
		_menuManager->GetCurrentButton() == EButton::Quit)
	{
		// If current menu is Begin menu -> go to Start button
		// Else if current menu is End menu -> go to Restart button
		_menuManager->SetCurrentButton(
			(_menuManager->GetCurrentMenu() == EMenuType::Begin) ?
			EButton::Start :
			EButton::Restart);
	}
	else if (_gameState == EGameState::Play)
	{
		_snake->UpdateDirection(EDirection::Up);
	}
}

void GameManager::ProcessLeftInput()
{
	if (_gameState == EGameState::Play)
	{
		_snake->UpdateDirection(EDirection::Left);
	}
}

void GameManager::ProcessDownInput()
{
	// If we're in menu and current button is not Quit (meaning Start or Restart)
	if (_gameState == EGameState::Menu &&
		_menuManager->GetCurrentButton() != EButton::Quit)
	{
		// Go to Quit button
		_menuManager->SetCurrentButton(EButton::Quit);
	}
	else if (_gameState == EGameState::Play)
	{
		_snake->UpdateDirection(EDirection::Bottom);
	}
}

void GameManager::ProcessRightInput()
{
	if (_gameState == EGameState::Play)
	{
		_snake->UpdateDirection(EDirection::Right);
	}
}
