
#include "stdafx.h"
#include "Snake.h"
#include "Utils.h"

Snake* Snake::_instance = nullptr;

Snake* Snake::GetInstance() 
{
	if (!_instance)
	{
		_instance = new Snake();
	}

	return _instance;
}

void Snake::Init(Renderer* pRenderer)
{
	_renderer = pRenderer;

	InitDirectionCoordMap();
}

void Snake::Start()
{
	CreateSnake();
}

void Snake::UpdateBuffer()
{
	ETile pieceType;
	char asciiChar;
	EColor foregroundColor;

	vector<SnakePiece>::iterator it;
	vector<SnakePiece>::iterator end = _snake.end();

	for (it = _snake.begin(); it != end; it++)
	{
		pieceType = it->pieceType;
		Utils::TileToChar(pieceType, asciiChar, foregroundColor);
		_renderer->DrawChar(it->coord.x, it->coord.y, asciiChar, foregroundColor);
	}
}

void Snake::UpdateDirection(EDirection pDirection)
{
	// Update only if new direction is not opposed to current direction
	// (left -> right, up -> bottom... = forbidden)
	if (pDirection != ((_currentDir + 2) % 4))
	{
		_currentDir = pDirection;
	}
}

int Snake::MoveSnake()
{
	// Check collisions before moving
	if (CheckCollisions() == INCORRECT_MOVE)
	{
		return INCORRECT_MOVE;
	}

	// Clear last snake tile
	int lastTileIndex = _snake.size() - 1;
	CleanLastTile(lastTileIndex);

	// Move all the snake body
	//As the next tile takes the coordinates of the previous one, we should think backward
	for (int tileIndex = lastTileIndex; tileIndex > 0; tileIndex--)
	{
		_snake[tileIndex].coord.x = _snake[tileIndex - 1].coord.x;
		_snake[tileIndex].coord.y = _snake[tileIndex - 1].coord.y;
	}

	// Move snake head according to direction
	_snake[0].coord.x += _directionsCoordMap.at(_currentDir).x;
	_snake[0].coord.y += _directionsCoordMap.at(_currentDir).y;

	return CORRECT_MOVE;
}

void Snake::EnlargeSnake()
{
	SnakePiece lastSnakePiece = _snake.back();
	_snake.push_back(SnakePiece(lastSnakePiece.coord.x, lastSnakePiece.coord.y + 1, lastSnakePiece.pieceType));
}

//Create a map with directions and coordinates
//Avoid making "switch case" or "if" each time we need to move the snake
void Snake::InitDirectionCoordMap()
{
	_directionsCoordMap.insert(pair<EDirection, Coord>(EDirection::Right, Coord(0, 1)));
	_directionsCoordMap.insert(pair<EDirection, Coord>(EDirection::Bottom, Coord(1, 0)));
	_directionsCoordMap.insert(pair<EDirection, Coord>(EDirection::Left, Coord(0, -1)));
	_directionsCoordMap.insert(pair<EDirection, Coord>(EDirection::Up, Coord(-1, 0)));

	_currentDir = EDirection::Left;
}

//Create the original snake with original pieces of the body
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
	int newX = _snake[0].coord.x + _directionsCoordMap.at(_currentDir).x;
	int newY = _snake[0].coord.y + _directionsCoordMap.at(_currentDir).y;
	ETile newTile = LevelManager::GetInstance()->GetTileFromBoard(newX, newY);

	if (newTile == ETile::Collectible)
	{
		EnlargeSnake();
		LevelManager::GetInstance()->UpdateCollectible(newX, newY, _snake);
	}
	else if (newTile == ETile::SnakeBody || newTile == ETile::Wall)
	{
		return INCORRECT_MOVE;
	}

	return CORRECT_MOVE;
}

void Snake::CleanLastTile(int pLastIndex)
{
	_renderer->ClearChar(_snake[pLastIndex].coord.x, _snake[pLastIndex].coord.y);
}


