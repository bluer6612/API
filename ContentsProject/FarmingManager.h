#pragma once
#include <EngineCore/GlobalVariable.h>

// Ό³Έν :
class UFarmingManager
{
public:
	// constrcuter destructer
	UFarmingManager();
	~UFarmingManager();

	// delete Function
	UFarmingManager(const UFarmingManager& _Other) = delete;
	UFarmingManager(UFarmingManager&& _Other) noexcept = delete;
	UFarmingManager& operator=(const UFarmingManager& _Other) = delete;
	UFarmingManager& operator=(UFarmingManager&& _Other) noexcept = delete;

	static int CropsNeedMoney[CropsCount] = {};
protected:

private:
	int i = 0;
};

