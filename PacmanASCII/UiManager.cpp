
#include "stdafx.h"
#include "UiManager.h"

UiManager* UiManager::_instance = nullptr;

UiManager* UiManager::GetInstance()
{
	if (!_instance)
	{
		_instance = new UiManager();
	}

	return _instance;
}

void UiManager::Init(Renderer* pRenderer)
{
	_renderer = pRenderer;
}

void UiManager::Start(int pScore)
{
	_score = pScore;
	DrawUi();
}

void UiManager::DrawUi()
{
	_renderer->DrawString(STRING_SCORE_X, STRING_SCORE_Y, STRING_SCORE, EColor::White);
	_renderer->DrawString(STRING_SCORE_COUNTER_X, STRING_SCORE_COUNTER_Y, to_string(_score), EColor::White);
	
	_renderer->DrawString(STRING_COMMANDS_X, STRING_COMMANDS_Y, STRING_COMMANDS, EColor::White);
	_renderer->DrawString(STRING_INFO_X, STRING_INFO_Y, STRING_INFO, EColor::White);
}