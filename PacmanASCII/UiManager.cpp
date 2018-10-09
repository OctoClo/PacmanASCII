
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

	livesStrings[0] = STRING_1_LIFE;
	livesStrings[1] = STRING_2_LIVES;
	livesStrings[2] = STRING_3_LIVES;
}

void UiManager::Start(int pScore, int pLives)
{
	_score = pScore;
	_lives = pLives;
	DrawUi();
}

void UiManager::DrawUi()
{
	_renderer->DrawString(STRING_LIVES_X, STRING_LIVES_Y, STRING_LIVES, EColor::White);
	_renderer->DrawString(STRING_NB_LIVES_X, STRING_NB_LIVES_Y, livesStrings[_lives - 1], EColor::White);

	_renderer->DrawString(STRING_SCORE_X, STRING_SCORE_Y, STRING_SCORE, EColor::White);
	_renderer->DrawString(STRING_SCORE_COUNTER_X, STRING_SCORE_COUNTER_Y, to_string(_score), EColor::White);
	
	_renderer->DrawString(STRING_INFO_X, STRING_INFO_Y, STRING_INFO, EColor::White);
}