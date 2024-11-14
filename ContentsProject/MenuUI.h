#pragma once
#include "Building.h"

class AMenuUI : public ABuilding
{
public:
		AMenuUI();
	~AMenuUI();

		AMenuUI(const AMenuUI& _Other) = delete;
	AMenuUI(AMenuUI&& _Other) noexcept = delete;
	AMenuUI& operator=(const AMenuUI& _Other) = delete;
	AMenuUI& operator=(AMenuUI&& _Other) noexcept = delete;

protected:

private:

};

