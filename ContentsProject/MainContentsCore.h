#pragma once
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

// Ό³Έν :
class MainContentsCore : public UContentsCore
{
public:
	// constrcuter destructer
	MainContentsCore();
	~MainContentsCore();

	// delete Function
	MainContentsCore(const MainContentsCore& _Other) = delete;
	MainContentsCore(MainContentsCore&& _Other) noexcept = delete;
	MainContentsCore& operator=(const MainContentsCore& _Other) = delete;
	MainContentsCore& operator=(MainContentsCore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick() override;

private:
	ULevel* TitleLevel;
	// UEngineWindow MyWindow;
};

