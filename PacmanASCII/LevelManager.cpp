
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
	FillBoard();
}

void LevelManager::Start()
{
	_score = START_SCORE;
	_lives = MAX_LIVES;
	_snakeHeadX = START_SNAKE_HEAD_X;
	_snakeHeadY = START_SNAKE_HEAD_Y;

	SpawnCollectible();
}

void LevelManager::Update()
{
	
}

void LevelManager::Render()
{
	EColor foregroundColor;
	ETile tile;
	char asciiChar;

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

void LevelManager::FillBoard()
{
	// Create 2 vertical walls
	int startX = 1;
	int startY = 0;
	int maxX = SCREEN_HEIGHT - 2;
	int maxY = SCREEN_WIDTH - 1;
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

	// Create snake
	_board[START_SNAKE_HEAD_X][START_SNAKE_HEAD_Y] = ETile::SnakeHead;

	for (int bodyPart = 1; bodyPart <= START_SNAKE_SIZE; bodyPart++)
	{
		_board[START_SNAKE_HEAD_X][START_SNAKE_HEAD_Y + bodyPart] = ETile::SnakeBody;
	}
}

void LevelManager::SpawnCollectible()
{
	// Spawn a collectible at a random position
	_board[10][20] = ETile::Collectible;
}

void LevelManager::TileToChar(ETile& pTile, char& pAsciiChar, EColor& pForeground)
{
	switch (pTile)
	{
	case ETile::Wall:
		pAsciiChar = '#';
		pForeground = EColor::Cyan;
		break;

	case ETile::SnakeHead:
		pAsciiChar = '@';
		pForeground = EColor::LightYellow;
		break;

	case ETile::SnakeBody:
		pAsciiChar = 'o';
		pForeground = EColor::Yellow;
		break;

	case ETile::Collectible:
		pAsciiChar = '*';
		pForeground = EColor::LightGreen;
		break;
	}
}