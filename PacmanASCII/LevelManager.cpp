
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

	InitDirectionCoordMap();
}

void LevelManager::InitDirectionCoordMap()
{
	_directionsCoordMap.insert(pair<EDirection, Coord>(EDirection::Right, Coord(0, 1)));
	_directionsCoordMap.insert(pair<EDirection, Coord>(EDirection::Bottom, Coord(1, 0)));
	_directionsCoordMap.insert(pair<EDirection, Coord>(EDirection::Left, Coord(0, -1)));
	_directionsCoordMap.insert(pair<EDirection, Coord>(EDirection::Up, Coord(-1, 0)));

	_currentDir = EDirection::Left;
}

void LevelManager::Start()
{
	_score = START_SCORE;

	_uiManager->Start(_score);

	FillBoard();

	CreateSnake();
	SpawnCollectible();

	RenderBoard();

	if (_firstGame)
	{
		_firstGame = false;
	}
}

void LevelManager::UpdateRenderer()
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

//CHANGER LE NOM
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

// Snake class
void LevelManager::CreateSnake()
{
	_snake.clear();

	_snake.push_back(SnakePiece(START_SNAKE_HEAD_X, START_SNAKE_HEAD_Y, ETile::SnakeHead));

	for (int snakeIndex = 1; snakeIndex < START_SNAKE_SIZE; snakeIndex++)
	{
		_snake.push_back(SnakePiece(START_SNAKE_HEAD_X, START_SNAKE_HEAD_Y + snakeIndex, ETile::SnakeBody));
	}
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

// Snake class
void LevelManager::CleanLastTile(int pLastIndex)
{
	_renderer->ClearChar(_snake[pLastIndex].x, _snake[pLastIndex].y);
}

// Snake class
void LevelManager::UpdateDirection(EDirection pDirection)
{
	// Check if new direction is not opposed to current direction
	// (left -> right, up -> bottom...)
	if (pDirection != ((_currentDir + 2) % 4))
	{
		_currentDir = pDirection;
	}
}

// Snake class
int LevelManager::MoveSnake()
{
	if (CheckCollisions() == INCORRECT_MOVE)
	{
		return INCORRECT_MOVE;
	}
	
	int lastTileIndex = _snake.size() - 1;

	CleanLastTile(lastTileIndex);

	for (int tileIndex = lastTileIndex; tileIndex > 0; tileIndex--)
	{
		_snake[tileIndex].x = _snake[tileIndex - 1].x;
		_snake[tileIndex].y = _snake[tileIndex - 1].y;
	}

	_snake[0].x += _directionsCoordMap.at(_currentDir).x;
	_snake[0].y += _directionsCoordMap.at(_currentDir).y;

	return CORRECT_MOVE;
}

int LevelManager::CheckCollisions()
{
	int newX = _snake[0].x + _directionsCoordMap.at(_currentDir).x;
	int newY = _snake[0].y + _directionsCoordMap.at(_currentDir).y;
	ETile newTile = _board[newX][newY];

	if (newTile == ETile::Collectible)
	{
		_score += SCORE_INCREMENT;
		_uiManager->SetScore(_score);
		EnlargeSnake();
		SpawnCollectible();
		_board[newX][newY] = ETile::Nothing;
	}
	else if (newTile == ETile::SnakeBody || newTile == ETile::Wall)
	{
		return INCORRECT_MOVE;
	}

	return CORRECT_MOVE;
}

void LevelManager::TileToChar(ETile& pTile, char& pAsciiChar, EColor& pForeground)
{
	switch (pTile)
	{
	case ETile::Wall:
		pAsciiChar = CHAR_WALL;
		pForeground = EColor::Cyan;
		break;

	case ETile::SnakeHead:
		pAsciiChar = CHAR_SNAKE_HEAD;
		pForeground = EColor::LightYellow;
		break;

	case ETile::SnakeBody:
		pAsciiChar = CHAR_SNAKE_BODY;
		pForeground = EColor::Yellow;
		break;

	case ETile::Collectible:
		pAsciiChar = CHAR_COLLECTIBLE;
		pForeground = EColor::LightGreen;
		break;
	}
}

// Snake class
void LevelManager::EnlargeSnake()
{
	SnakePiece lastSnakePiece = _snake.back();

	_snake.push_back(SnakePiece(lastSnakePiece.x , lastSnakePiece.y + 1, lastSnakePiece.pieceType));
}
