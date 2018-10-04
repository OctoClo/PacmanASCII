#ifndef RENDERER_H
#define RENDERER_H

#pragma once

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 25

#include "stdafx.h"

enum EColor {
	Transparent,
	Blue,
	Green,
	Cyan,
	Red,
	Purple,
	Yellow,
	White,
	Grey,
	LightBlue,
	LightGreen,
	LightCyan,
	LightRed,
	LightPurple,
	LightYellow,
	LightWhite,
	LightGrey
};

class Renderer
{
public:
	void Init();

	void Render();

	void DrawChar(int pX, int pY, char pAsciiChar, EColor pForeground, EColor pBackground = EColor::Transparent);

	static Renderer* GetInstance();

private:
	int GetASCIIColor(EColor pForeground, EColor pBackground);

	HANDLE _handleOutput;
	COORD _screenBufferSize;
	COORD _screenBufferCoord;
	SMALL_RECT _rectRegion;
	CHAR_INFO _screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

	static Renderer* _instance;
};

#endif
