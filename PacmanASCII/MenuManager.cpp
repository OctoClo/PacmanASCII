
#include "stdafx.h"
#include "MenuManager.h"

MenuManager* MenuManager::_instance = nullptr;

MenuManager* MenuManager::GetInstance()
{
	if (!_instance)
	{
		_instance = new MenuManager();
	}

	return _instance;
}

void MenuManager::Init(Renderer* pRenderer)
{
	_renderer = pRenderer;
	LaunchBeginMenu();
}

void MenuManager::LaunchBeginMenu()
{
	_currentMenu = EMenuType::Begin;
	_currentButton = EButton::Start;
}

void MenuManager::LaunchEndMenu()
{
	_currentMenu = EMenuType::End;
	_currentButton = EButton::Restart;
}

void MenuManager::UpdateRenderer()
{
	DisplayMenu();

	switch (_currentButton)
	{
	case EButton::Start:
		_renderer->DrawChar(QUIT_BUTTON_X, ARROW_Y, ' ', EColor::Transparent);
		_renderer->DrawChar(START_BUTTON_X, ARROW_Y, '-', EColor::LightPurple);
		break;
	case EButton::Restart:
		_renderer->DrawChar(QUIT_BUTTON_X, ARROW_Y, ' ', EColor::Transparent);
		_renderer->DrawChar(RESTART_BUTTON_X, ARROW_Y, '-', EColor::LightPurple);
		break;
	case EButton::Quit:
		_renderer->DrawChar(START_BUTTON_X, ARROW_Y, ' ', EColor::Transparent);
		_renderer->DrawChar(QUIT_BUTTON_X, ARROW_Y, '-', EColor::LightPurple);
		break;
	}
}

void MenuManager::DisplayMenu()
{
	switch (_currentMenu)
	{
	case EMenuType::Begin:
		DisplayButton(START_BUTTON_TEXT, START_BUTTON_X, BUTTON_Y);
		DisplayButton(QUIT_BUTTON_TEXT, QUIT_BUTTON_X, BUTTON_Y);
		break;

	case EMenuType::End:
		DisplayButton(RESTART_BUTTON_TEXT, RESTART_BUTTON_X, BUTTON_Y);
		DisplayButton(QUIT_BUTTON_TEXT, QUIT_BUTTON_X, BUTTON_Y);
		break;
	}
}

void MenuManager::DisplayButton(string pButton, int pX, int pY)
{
	int length = pButton.length();
	for (int currentChar = 0; currentChar < length; currentChar++)
	{
		_renderer->DrawChar(pX, pY + currentChar, pButton[currentChar], EColor::White);
	}
}