#pragma once

#define STRING_LIVES "LIFES: "
#define STRING_LIVES_X 0
#define STRING_LIVES_Y 1

#define STRING_3_LIVES "OOO"
#define STRING_2_LIVES "OOØ"
#define STRING_1_LIFE "OØØ"
#define STRING_NB_LIVES_X 0
#define STRING_NB_LIVES_Y 8

#define STRING_SCORE "SCORE: "
#define STRING_SCORE_X 0
#define STRING_SCORE_Y 87

#define STRING_SCORE_COUNTER_X 0
#define STRING_SCORE_COUNTER_Y 94

#define STRING_INFO "Press ESC to quit"
#define STRING_INFO_X 24
#define STRING_INFO_Y 80

#include "stdafx.h"
#include "Enums.h"
#include "Renderer.h"

class UiManager
{
public:
	void Init(Renderer* pRenderer);
	void Start(int pScore, int pLives);

	void SetScore(int pScore) { _score = pScore; DrawUi(); }
	int GetScore() { return _score; }

	void SetLives(int pLives) { _lives = pLives; DrawUi(); }
	int GetLives() { return _lives; }

	static UiManager* GetInstance();

private:
	void DrawUi();

	int _score;
	int _lives;

	string livesStrings[3];

	Renderer* _renderer;

	static UiManager* _instance;
};