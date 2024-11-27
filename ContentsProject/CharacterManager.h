#pragma once

// Ό³Έν :
class ACharacterManager : public AActor
{
public:
	// constrcuter destructer
	ACharacterManager();
	~ACharacterManager();

	// delete Function
	ACharacterManager(const ACharacterManager& _Other) = delete;
	ACharacterManager(ACharacterManager&& _Other) noexcept = delete;
	ACharacterManager& operator=(const ACharacterManager& _Other) = delete;
	ACharacterManager& operator=(ACharacterManager&& _Other) noexcept = delete;

	void Watering(FVector2D _Location)
	{

	}

	void SetUIManager(AUIManager* const _UIManager)
	{
		UIManager = _UIManager;
	}

protected:

private:
	AUIManager* UIManager = nullptr;

};