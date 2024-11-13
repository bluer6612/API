#pragma once
#include "Building.h"

// Ό³Έν :
class AMenuUI : public ABuilding
{
public:
	// constrcuter destructer
	AMenuUI();
	~AMenuUI();

	// delete Function
	AMenuUI(const AMenuUI& _Other) = delete;
	AMenuUI(AMenuUI&& _Other) noexcept = delete;
	AMenuUI& operator=(const AMenuUI& _Other) = delete;
	AMenuUI& operator=(AMenuUI&& _Other) noexcept = delete;

protected:

private:

};

