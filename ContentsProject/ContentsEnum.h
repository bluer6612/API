#pragma once


enum class ERenderOrder
{
	COLMAP = -1000,
	BACKGROUND = -999,
	ZERO = 0,
	BUILDINGDOWN = 9,
	BUILDING = 10,
	BUILDINGTILE= 11,
	PLAYER = 12,
	BUILDINGUP = 13,
	UIDOWN = 9999,
	UI = 10000,
	UIUP = 10001,
	UITOP = 10002,
	TITLE = 11000,
	FADE = 20000,
	CURSOR = 30000,
};

enum class ECollisionGroup
{
	PlayerBody,
	MonsterBody,
};
