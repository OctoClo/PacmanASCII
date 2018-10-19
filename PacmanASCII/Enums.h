#ifndef ENUMS_H
#define ENUMS_H

#pragma once

enum EDirection
{
	Right,
	Bottom,
	Left,
	Up
};

enum EGameState
{
	Play,
	Menu,
	Exit
};

enum EMenuType
{
	Begin,
	End
};

enum EButton
{
	Start,
	Restart,
	Quit
};

enum ETile
{
	Nothing,
	Wall,
	SnakeHead,
	SnakeBody,
	Collectible
};

enum EColor {
	Transparent,
	Blue,
	Green,
	Cyan,
	Red,
	Purple,
	Yellow,
	White,
	Grey,
	LightBlue,
	LightGreen,
	LightCyan,
	LightRed,
	LightPurple,
	LightYellow,
	LightWhite,
	LightGrey
};

#endif
