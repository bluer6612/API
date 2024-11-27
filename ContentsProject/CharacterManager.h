#pragma once

// Ό³Έν :
class ACharacterManager
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

protected:

private:

};