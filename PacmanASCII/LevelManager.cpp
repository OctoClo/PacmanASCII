
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

	CreateSnake();
	SpawnCollectible();

	RenderBoard();
}

void LevelManager::Update()
{
	
}

void LevelManager::Render()
{
	ETile pieceType;
	char asciiChar;
	EColor foregroundColor;

	// Why not
	vector<SnakePiece>::iterator it;
	vector<SnakePiece>::iterator end = _snake.end();

	for (it = _snake.begin(); it != end; it++)
	{
		pieceType = it->pieceType;
		TileToChar(pieceType, asciiChar, foregroundColor);
		_renderer->DrawChar(it->x, it->y, asciiChar, foregroundColor);
	}
}

void LevelManager::RenderBoard()
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

void LevelManager::CreateSnake()
{
	_snake.push_back(SnakePiece(START_SNAKE_HEAD_X, START_SNAKE_HEAD_Y, ETile::SnakeHead));

	for (int snakeIndex = 1; snakeIndex < START_SNAKE_SIZE; snakeIndex++)
	{
		_snake.push_back(SnakePiece(START_SNAKE_HEAD_X, START_SNAKE_HEAD_Y + snakeIndex, ETile::SnakeBody));
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
}

void LevelManager::SpawnCollectible()
{
	// Spawn a collectible at a random position
	_board[10][20] = ETile::Collectible;
}

int LevelManager::CheckCollisions()
{
	return CORRECT_MOVE;
}

void LevelManager::CleanLastTile(int pLastIndex)
{
	_renderer->ClearChar(_snake[pLastIndex].x, _snake[pLastIndex].y);
}

int LevelManager::MoveSnake(int pDirX, int pDirY)
{
	int lastTileIndex = _snake.size() - 1;

	CleanLastTile(lastTileIndex);

	for (int tileIndex = lastTileIndex; tileIndex > 0; tileIndex--)
	{
		_snake[tileIndex].x = _snake[tileIndex - 1].x;
		_snake[tileIndex].y = _snake[tileIndex - 1].y;
	}

	_snake[0].x += pDirX;
	_snake[0].y += pDirY;

	//Block the snake from moving outside the boards
	//if ((snakeHeadCoord.x + pDirX) < 0 || (snakeHeadCoord.x + pDirX) > SCREEN_HEIGHT - 1) pDirX = 0;
	//if ((snakeHeadCoord.y + pDirY) < 0 || (snakeHeadCoord.y + pDirY) > SCREEN_WIDTH - 1) pDirY = 0;

	return CORRECT_MOVE;
}

void LevelManager::UpdateSnake() {

	SnakePiece lastSnakePiece = _snake.back();

	_snake.push_back(SnakePiece(lastSnakePiece.x , lastSnakePiece.y + 1, lastSnakePiece.pieceType));
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