#pragma once

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 25

#include "stdafx.h"
#include "Enums.h"

class Renderer
{
public:
	void Init();

	void Render();

	void ClearChar(int pX, int pY);
	void ClearScreen();
	void DrawString(int pX, int pY,const string& pString, EColor pForeground, EColor pBackground = EColor::Transparent);
	void DrawChar(int pX, int pY, char pAsciiChar, EColor pForeground, EColor pBackground = EColor::Transparent);

	static Renderer* GetInstance();

private:
	int GetASCIIColor(EColor pForeground, EColor pBackground);

	HANDLE _handleOutput = nullptr;
	COORD _screenBufferSize = { 0,0 };
	COORD _screenBufferCoord = { 0,0 };
	SMALL_RECT _rectRegion = { 0,0,0,0 };
	CHAR_INFO _screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH] = {};

	static Renderer* _instance;
};
