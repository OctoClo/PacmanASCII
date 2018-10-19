#pragma once

#define MOVE_INTERVAL 1

#include "stdafx.h"
#include "Enums.h"

class Timer
{
public:
	static void Start();
	static bool CanMove();

private:
	static clock_t startTime;
};