#pragma once

#define STRING_SCORE "SCORE: "
#define STRING_SCORE_X 0
#define STRING_SCORE_Y 45

#define STRING_SCORE_COUNTER_X 0
#define STRING_SCORE_COUNTER_Y 52

#define STRING_INFO "Press ESC to quit"
#define STRING_INFO_X 24
#define STRING_INFO_Y 82

#define STRING_COMMANDS "Move with ZQSD"
#define STRING_COMMANDS_X 24
#define STRING_COMMANDS_Y 2

#include "stdafx.h"
#include "Enums.h"
#include "Renderer.h"

class UiManager
{
public:
	void Init(Renderer* pRenderer);
	void Start(int pScore);

	void SetScore(int pScore) { _score = pScore; DrawUi(); }
	int GetScore() { return _score; }

	static UiManager* GetInstance();

private:
	void DrawUi();

	int _score;

	Renderer* _renderer;

	static UiManager* _instance;
};