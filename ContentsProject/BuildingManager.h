#pragma once

// ���� :
class ABuildingManager
{
public:
	// constrcuter destructer
	ABuildingManager();
	~ABuildingManager();

	// delete Function
	ABuildingManager(const ABuildingManager& _Other) = delete;
	ABuildingManager(ABuildingManager&& _Other) noexcept = delete;
	ABuildingManager& operator=(const ABuildingManager& _Other) = delete;
	ABuildingManager& operator=(ABuildingManager&& _Other) noexcept = delete;

protected:

private:

};

