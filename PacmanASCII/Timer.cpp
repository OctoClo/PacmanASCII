
#include "stdafx.h"
#include "Timer.h"

clock_t Timer::startTime = 0;

void Timer::Start()
{
	Timer::startTime = clock();
}

bool Timer::CanMove()
{
	if ((clock() - Timer::startTime) >= MOVE_INTERVAL_MILLIS)
	{
		Timer::Start();
		return true;
	}

	return false;
}