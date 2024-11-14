#pragma once
#include "Building.h"

class AMenuPanelUI : public ABuilding
{
public:
	AMenuPanelUI();
	~AMenuPanelUI();

	AMenuPanelUI(const AMenuPanelUI& _Other) = delete;
	AMenuPanelUI(AMenuPanelUI&& _Other) noexcept = delete;
	AMenuPanelUI& operator=(const AMenuPanelUI& _Other) = delete;
	AMenuPanelUI& operator=(AMenuPanelUI&& _Other) noexcept = delete;

protected:

private:
	class USpriteRenderer* SpriteRendererTap = nullptr;
};

