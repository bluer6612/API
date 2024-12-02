#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include "TileMap.h"
#include "UIManager.h"

class APlayGameMode : public AGameMode
{
public:
	
	APlayGameMode();
	~APlayGameMode();

	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

	void SetUIManager(AUIManager* const _UIManager)
	{
		UIManager = _UIManager;
	}

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;

private:
	class AScore* Score = nullptr;

	AUIManager* UIManager = nullptr;
	USoundPlayer BGMPlayer;
};

