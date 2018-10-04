
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

		switch (_gameState)
		{
		case EGameState::Menu:
			// Listen for arrow / enter keys
			switch (key)
			{
			case KEY_ENTER:
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
				break;

			case KEY_Z: case KEY_Z_CAPITAL:
				if (_uiManager->GetCurrentButton() == EButton::Quit)
				{
					if (_uiManager->GetCurrentMenu() == EMenuType::Begin)
					{
						_uiManager->SetCurrentButton(
							(_uiManager->GetCurrentMenu() == EMenuType::Begin) ?
							EButton::Start : EButton::Restart);
					}
				}
				break;

			case KEY_S: case KEY_S_CAPITAL:
				if (_uiManager->GetCurrentButton() != EButton::Quit)
				{
					_uiManager->SetCurrentButton(EButton::Quit);
				}
				break;
			}
			break;

		case EGameState::Play:
			// Listen for arrow keys
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