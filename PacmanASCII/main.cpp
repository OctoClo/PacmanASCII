// PacmanASCII.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Enums.h"
#include "GameManager.h"
#include "Renderer.h"

#define WIN32_LEAN_AND_MEAN

int main()
{
	GameManager* gm = GameManager::GetInstance();
	gm->GameLoop();

	return 0;
}

