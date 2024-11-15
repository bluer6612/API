#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include "TitleLogo.h"
#include "PlayMap.h"
#include "TileMap.h"

class APlayGameMode : public AGameMode
{
public:
	
	APlayGameMode();
	~APlayGameMode();

	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;

private:
	class AScore* Score;
	ATileMap* WallTileMap = nullptr;
	ATileMap* GroundTileMap = nullptr;
};

