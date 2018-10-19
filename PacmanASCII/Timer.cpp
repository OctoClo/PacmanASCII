
#include "stdafx.h"
#include "Timer.h"

clock_t Timer::_startTime = 0;

void Timer::Start()
{
	Timer::_startTime = clock();
}

bool Timer::CanMove()
{
	if ((clock() - Timer::_startTime) >= MOVE_INTERVAL_MILLIS)
	{
		Timer::Start();
		return true;
	}

	return false;
}