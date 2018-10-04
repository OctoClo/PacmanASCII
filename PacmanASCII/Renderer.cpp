
#include "stdafx.h"
#include "Renderer.h"

Renderer* Renderer::_instance = nullptr;

Renderer* Renderer::GetInstance()
{
	if (!_instance)
	{
		_instance = new Renderer();
	}

	return _instance;
}

void Renderer::Init()
{
	// Initialize console buffer
	_handleOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	_screenBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	_screenBufferCoord = { 0, 0 };
	_rectRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	// Hide blinking caret
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(_handleOutput, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(_handleOutput, &cursorInfo);
}

void Renderer::Render()
{
	WriteConsoleOutput(_handleOutput, (CHAR_INFO *)_screenBuffer, _screenBufferSize,
		_screenBufferCoord, &_rectRegion);
}

void Renderer::DrawChar(int pX, int pY, char pAsciiChar, EColor pForeground, EColor pBackground)
{
	_screenBuffer[pX][pY].Char.AsciiChar = pAsciiChar;
	_screenBuffer[pX][pY].Attributes = GetASCIIColor(pForeground, pBackground);
}

int Renderer::GetASCIIColor(EColor pForeground, EColor pBackground)
{
	int output = 0;
	output = pForeground + (pBackground * 16);
	return output;
}