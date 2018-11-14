#include "stdafx.h"
#include "GameManager.h"

//Singleton, as a manager we need only one instance
//Easiest way to access public functions

GameManager* GameManager::_instance = nullptr;

GameManager* GameManager::GetInstance() 
{
	if (!_instance) 
	{
		_instance = new GameManager();
	}

	return _instance;
}

//Central function of the game
//The main logic is: 1) Check inputs 2) Update the buffer 3) Update the render
void GameManager::GameLoop()
{
	Init();

	while (_gameState != EGameState::Exit)
	{
		ProcessInputs();
		UpdateBuffer();
		Render();
	}
}

void GameManager::Init()
{
	_gameState = EGameState::Menu;

	_renderer = Renderer::GetInstance();
	_renderer->Init();

	_snake = Snake::GetInstance();
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

void GameManager::UpdateBuffer()
{
	switch (_gameState)
	{
	case EGameState::Menu:
		_menuManager->UpdateBuffer();
		break;

	case EGameState::Play:
		_snake->UpdateBuffer();

		// Move snake only if the timer says so
		if (Timer::CanMove())
		{
			// Game over happens if snake does an incorrect move
			int gameOver = (_snake->MoveSnake() != CORRECT_MOVE);

			if (gameOver)
			{
				_gameState = EGameState::Menu;
				_menuManager->LaunchEndMenu();
			}
		}

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
	if (_gameState == EGameState::Menu &&
		_menuManager->GetCurrentButton() == EButton::Quit)
	{
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
	if (_gameState == EGameState::Menu &&
		_menuManager->GetCurrentButton() != EButton::Quit)
	{
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
