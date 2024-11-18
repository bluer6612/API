#pragma once


enum class ERenderOrder
{
	COLMAP = -1000,
	BACKGROUND = -999,
	ZERO = 0,
	BUILDINGDOWN = 8,
	PLAYER = 9,
	BUILDING = 10,
	BUILDINGUP = 11,
	UIDOWN = 9999,
	UI = 10000,
	UIUP = 10001,
	TITLE = 11000,
	FADE = 20000,
};

enum class ECollisionGroup
{
	PlayerBody,
	MonsterBody,
};
