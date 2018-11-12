
#include "stdafx.h"
#include "Timer.h"

clock_t Timer::_startTime = 0;

//Get the current hour of the computer
void Timer::Start()
{
	Timer::_startTime = clock();
}

bool Timer::CanMove()
{
	// If time is over given interval, time to move !
	if ((clock() - Timer::_startTime) >= MOVE_INTERVAL_MILLIS)
	{
		Timer::Start();
		return true;
	}

	return false;
}