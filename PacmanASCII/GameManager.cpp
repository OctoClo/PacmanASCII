
#include "stdafx.h"
#include "GameManager.h"

GameManager GameManager::instance = GameManager();

GameManager& GameManager::getInstance()
{
	return instance;
}