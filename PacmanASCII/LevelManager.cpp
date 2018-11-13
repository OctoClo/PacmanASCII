
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

	srand((int)time(0));
}

void LevelManager::Start()
{
	_score = START_SCORE;
	_uiManager->Start(_score);

	FillBoard();
	SpawnCollectible();
	UpdateBuffer();

	if (_firstGame)
	{
		_firstGame = false;
	}
}

void LevelManager::UpdateCollectible(int pEatenCollectibleX, int pEatenCollectibleY, vector<SnakePiece> pSnake)
{
	_score += SCORE_INCREMENT;
	_uiManager->SetScore(_score);
	SpawnCollectible(pSnake);
	_board[pEatenCollectibleX][pEatenCollectibleY] = ETile::Nothing;
}

ETile LevelManager::GetTileFromBoard(int pX, int pY)
{
	return _board[pX][pY];
}

//Fill the game board with the walls of the level
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
		// Reinitialize collectible's position to nothing if new game
		_board[_collectibleCoord.x][_collectibleCoord.y] = ETile::Nothing;
	}
}

void LevelManager::UpdateBuffer()
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
				Utils::TileToChar(tile, asciiChar, foregroundColor);
				_renderer->DrawChar(x, y, asciiChar, foregroundColor);
			}
		}
	}
}

void LevelManager::SpawnCollectible(vector<SnakePiece> pSnake)
{
	int randomX, randomY;

	do
	{
		//Avoid the collectible to spawn in the walls
		randomX = Utils::Clamp(rand() % SCREEN_HEIGHT, 2, SCREEN_HEIGHT - 3);
		randomY = Utils::Clamp(rand() % SCREEN_WIDTH, 1, SCREEN_WIDTH - 2);
	} while (IsPositionInSnake(randomX, randomY, pSnake));
	
	_board[randomX][randomY] = ETile::Collectible;

	ETile tile = ETile::Collectible;
	char asciiChar;
	EColor foregroundColor;
	Utils::TileToChar(tile, asciiChar, foregroundColor);
	_renderer->DrawChar(randomX, randomY, asciiChar, foregroundColor);

	_collectibleCoord = Coord(randomX, randomY);
}

//Check if a position is in the snake's body, avoid the collectible to spawn inside
bool LevelManager::IsPositionInSnake(int pX, int pY, vector<SnakePiece> pSnake)
{
	if (pSnake.size() > 0)
	{
		vector<SnakePiece>::iterator it;
		vector<SnakePiece>::iterator end = pSnake.end();

		for (it = pSnake.begin(); it != end; it++)
		{
			if (it->coord.x == pX && it->coord.y == pY)
				return true;
		}
	}

	return false;
}

