
#include "stdafx.h"
#include "LevelManager.h"

LevelManager* LevelManager::_instance = nullptr;

LevelManager* LevelManager::GetInstance()
{
	if (!_instance)
	{
		_instance = new LevelManager();
	}

	return _instance;
}

void LevelManager::Init(Renderer* pRenderer)
{
	_renderer = pRenderer;
	_firstGame = true;

	_uiManager = UiManager::GetInstance();
	_uiManager->Init(_renderer);
}

void LevelManager::Start()
{
	_score = START_SCORE;
	_uiManager->Start(_score);

	FillBoard();
	SpawnCollectible();
	UpdateRendererOnce();

	if (_firstGame)
	{
		_firstGame = false;
	}
}

void LevelManager::UpdateCollectible(int pEatenCollectibleX, int pEatenCollectibleY)
{
	_score += SCORE_INCREMENT;
	_uiManager->SetScore(_score);
	SpawnCollectible();
	_board[pEatenCollectibleX][pEatenCollectibleY] = ETile::Nothing;
}

ETile LevelManager::GetTileFromBoard(int pX, int pY)
{
	return _board[pX][pY];
}

void LevelManager::FillBoard()
{
	int startX = 1;
	int startY = 0;
	int maxX = SCREEN_HEIGHT - 2;
	int maxY = SCREEN_WIDTH - 1;

	// Create 2 vertical walls
	for (int x = startX; x < maxX; x++)
	{
		_board[x][startY] = ETile::Wall;
		_board[x][maxY] = ETile::Wall;
	}

	// Create 2 horizontal walls
	for (int y = startY; y < maxY; y++)
	{
		_board[startX][y] = ETile::Wall;
		_board[maxX][y] = ETile::Wall;
	}

	if (!_firstGame)
	{
		_board[_collectibleCoord.x][_collectibleCoord.y] = ETile::Nothing;
	}
}

void LevelManager::UpdateRendererOnce()
{
	ETile tile;
	char asciiChar;
	EColor foregroundColor;

	for (int x = 0; x < SCREEN_HEIGHT; x++)
	{
		for (int y = 0; y < SCREEN_WIDTH; y++)
		{
			tile = _board[x][y];
			if (tile != ETile::Nothing)
			{
				TileToChar(tile, asciiChar, foregroundColor);
				_renderer->DrawChar(x, y, asciiChar, foregroundColor);
			}
		}
	}
}

void LevelManager::SpawnCollectible()
{
	int randomX = rand() % SCREEN_HEIGHT;
	int randomY = rand() % SCREEN_WIDTH;

	_board[randomX][randomY] = ETile::Collectible;

	ETile tile = ETile::Collectible;
	char asciiChar;
	EColor foregroundColor;
	TileToChar(tile, asciiChar, foregroundColor);
	_renderer->DrawChar(randomX, randomY, asciiChar, foregroundColor);

	_collectibleCoord = Coord(randomX, randomY);
}

void LevelManager::TileToChar(ETile& pTile, char& pAsciiChar, EColor& pForeground)
{
	switch (pTile)
	{
	case ETile::Wall:
		pAsciiChar = CHAR_WALL;
		pForeground = EColor::Cyan;
		break;

	case ETile::Collectible:
		pAsciiChar = CHAR_COLLECTIBLE;
		pForeground = EColor::LightGreen;
		break;
	}
}
