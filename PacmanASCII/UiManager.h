#pragma once

#define START_BUTTON_TEXT "START"
#define START_BUTTON_X 5

#define RESTART_BUTTON_TEXT "RESTART"
#define RESTART_BUTTON_X 5

#define QUIT_BUTTON_TEXT "QUIT"
#define QUIT_BUTTON_X 10

#include "stdafx.h"
#include "Enums.h"
#include "Renderer.h"

#define BUTTON_Y (SCREEN_WIDTH / 2)
#define ARROW_Y (BUTTON_Y - 2)

class UiManager
{
public:
	void Init(Renderer* pRenderer);

	void LaunchBeginMenu();
	void LaunchEndMenu();

	void Render();

	EMenuType GetCurrentMenu() { return _currentMenu; }
	void SetCurrentButton(EButton pButton) { _currentButton = pButton; }
	EButton GetCurrentButton() { return _currentButton; }

	static UiManager* GetInstance();

private:
	void DisplayMenu();
	void DisplayButton(string pButton, int pX, int pY);

	EMenuType _currentMenu;
	EButton _currentButton;
	Renderer* _renderer;

	static UiManager* _instance;
};