#define WIN32_LEAN_AND_MEAN

#include "stdafx.h"
#include "Enums.h"
#include "GameManager.h"
#include "Renderer.h"

int main()
{
	GameManager* gm = GameManager::GetInstance();
	gm->GameLoop();

	return 0;
}

