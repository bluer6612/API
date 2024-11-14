#pragma once


enum class ERenderOrder
{
	COLMAP = -1000,
	BACKGROUND = -999,
	PLAYER = 9,
	BUILDING = 10,
	UI = 10000,
	TITLE = 11000,
	FADE = 20000,
};

enum class ECollisionGroup
{
	PlayerBody,
	MonsterBody,
};
