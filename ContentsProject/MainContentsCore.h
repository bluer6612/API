#pragma once
#include <EngineCore/EngineAPICore.h>

class MainContentsCore : public UContentsCore
{
public:
	MainContentsCore();
	~MainContentsCore();

	MainContentsCore(const MainContentsCore& _Other) = delete;
	MainContentsCore(MainContentsCore&& _Other) noexcept = delete;
	MainContentsCore& operator=(const MainContentsCore& _Other) = delete;
	MainContentsCore& operator=(MainContentsCore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick() override;

private:
};

