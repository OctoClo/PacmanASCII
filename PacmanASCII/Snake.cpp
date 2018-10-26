
#include "stdafx.h"
#include "Snake.h"

void Snake::Init(Renderer* pRenderer)
{
	_renderer = pRenderer;

	InitDirectionCoordMap();
}

void Snake::Start()
{
	CreateSnake();
}

void Snake::UpdateRenderer()
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

void Snake::UpdateDirection(EDirection pDirection)
{
	// Check if new direction is not opposed to current direction
	// (left -> right, up -> bottom...)
	if (pDirection != ((_currentDir + 2) % 4))
	{
		_currentDir = pDirection;
	}
}

int Snake::MoveSnake()
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

void Snake::EnlargeSnake()
{
	SnakePiece lastSnakePiece = _snake.back();

	_snake.push_back(SnakePiece(lastSnakePiece.x, lastSnakePiece.y + 1, lastSnakePiece.pieceType));
}

void Snake::InitDirectionCoordMap()
{
	_directionsCoordMap.insert(pair<EDirection, Coord>(EDirection::Right, Coord(0, 1)));
	_directionsCoordMap.insert(pair<EDirection, Coord>(EDirection::Bottom, Coord(1, 0)));
	_directionsCoordMap.insert(pair<EDirection, Coord>(EDirection::Left, Coord(0, -1)));
	_directionsCoordMap.insert(pair<EDirection, Coord>(EDirection::Up, Coord(-1, 0)));

	_currentDir = EDirection::Left;
}

void Snake::CreateSnake()
{
	_snake.clear();

	_snake.push_back(SnakePiece(START_SNAKE_HEAD_X, START_SNAKE_HEAD_Y, ETile::SnakeHead));

	for (int snakeIndex = 1; snakeIndex < START_SNAKE_SIZE; snakeIndex++)
	{
		_snake.push_back(SnakePiece(START_SNAKE_HEAD_X, START_SNAKE_HEAD_Y + snakeIndex, ETile::SnakeBody));
	}
}

int Snake::CheckCollisions()
{
	int newX = _snake[0].x + _directionsCoordMap.at(_currentDir).x;
	int newY = _snake[0].y + _directionsCoordMap.at(_currentDir).y;
	ETile newTile = LevelManager::GetInstance()->GetTileFromBoard(newX, newY);

	if (newTile == ETile::Collectible)
	{
		LevelManager::GetInstance()->UpdateCollectible(newX, newY);
		EnlargeSnake();
	}
	else if (newTile == ETile::SnakeBody || newTile == ETile::Wall)
	{
		return INCORRECT_MOVE;
	}

	return CORRECT_MOVE;
}

void Snake::CleanLastTile(int pLastIndex)
{
	_renderer->ClearChar(_snake[pLastIndex].x, _snake[pLastIndex].y);
}

void Snake::TileToChar(ETile& pTile, char& pAsciiChar, EColor& pForeground)
{
	switch (pTile)
	{
	case ETile::SnakeHead:
		pAsciiChar = CHAR_SNAKE_HEAD;
		pForeground = EColor::LightYellow;
		break;

	case ETile::SnakeBody:
		pAsciiChar = CHAR_SNAKE_BODY;
		pForeground = EColor::Yellow;
		break;
	}
}

