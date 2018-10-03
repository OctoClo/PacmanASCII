#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#pragma once

class GameManager
{
public:
	static GameManager* GetInstance();

private:
	static GameManager* _instance;		
};
#endif