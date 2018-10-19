#pragma once

#define MOVE_INTERVAL_MILLIS 100

#include "stdafx.h"
#include "Enums.h"

class Timer
{
public:
	static void Start();
	static bool CanMove();

private:
	static clock_t _startTime;
};