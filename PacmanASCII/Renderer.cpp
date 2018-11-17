
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

void Renderer::ClearChar(int pX, int pY)
{
	_screenBuffer[pX][pY] = {};
}

void Renderer::ClearScreen()
{
	for (int x = 0; x < SCREEN_HEIGHT; x++)
	{
		for (int y = 0; y < SCREEN_WIDTH; y++)
		{
			_screenBuffer[x][y] = {};
		}
	}
}

void Renderer::DrawString(int pX, int pY,const string& pString, EColor pForeground, EColor pBackground)
{
	int length = pString.length();

	for (int i = 0; i < length; i++)
	{
		_screenBuffer[pX][pY + i].Char.AsciiChar = pString[i];
		_screenBuffer[pX][pY + i].Attributes = GetASCIIColor(pForeground, pBackground);
	}
}

void Renderer::DrawChar(int pX, int pY, char asciiChar, EColor pForeground, EColor pBackground)
{
	_screenBuffer[pX][pY].Char.AsciiChar = asciiChar;
	_screenBuffer[pX][pY].Attributes = GetASCIIColor(pForeground, pBackground);
}

int Renderer::GetASCIIColor(EColor pForeground, EColor pBackground)
{
	return (pForeground + (pBackground * 16));
}