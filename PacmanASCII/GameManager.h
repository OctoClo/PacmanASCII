#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#pragma once

class GameManager
{
public:
	static GameManager& getInstance();

private:
	GameManager();

	static GameManager instance;
};

#endif