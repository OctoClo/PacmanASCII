
#include "stdafx.h"
#include "GameManager.h"


/*GameManager GameManager::instance = GameManager();

GameManager* GameManager::getInstance()
{
	return &instance;
}*/

GameManager* GameManager::_instance = NULL;

/*GameManager::GameManager()
{
	// do init stuff
}*/

GameManager* GameManager::GetInstance()
{
	if (_instance == NULL) {
		_instance = new GameManager();
	}
	return _instance;
}

void GameManager::Test() {
	printf("instance appelée");
}