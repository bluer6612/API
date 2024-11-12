#include "PreCompile.h"
#include "Building.h"

ABuilding::ABuilding()
{
}

ABuilding::~ABuilding()
{
}

void ABuilding::ModelAdd(int _ModelNumber, float _Size, int _X, int _Y, int _Order = 0)
{
	Model[index] = CreateDefaultSubObject<USpriteRenderer>();
	Model[index]->SetSprite("House");
	Model[index]->CreateAnimation("Idle", "House", _ModelNumber, _ModelNumber, 0);
	Model[index]->SetSpriteScale(_Size);
	Model[index]->SetComponentLocation({ static_cast<float>(ScreenX * 0.5 + _X), static_cast<float>((ScreenY * 0.3) * 0.275 + _Y) });
	Model[index]->SetOrder(_Order);
	++index;
}

void ABuilding::ModelAdd(int _ModelNumber, int _SizeX, int _SizeY, int _X, int _Y, int _Order = 0)
{
	Model[index] = CreateDefaultSubObject<USpriteRenderer>();
	Model[index]->SetSprite("House");
	Model[index]->CreateAnimation("Idle", "House", _ModelNumber, _ModelNumber, 0);
	Model[index]->SetComponentScale({ static_cast<float>(_SizeX * 2), static_cast<float>(_SizeY * 2) });
	Model[index]->SetComponentLocation({ static_cast<float>(ScreenX * 0.5 + _X), static_cast<float>((ScreenY * 0.3) * 0.275 + _Y) });
	Model[index]->SetOrder(_Order);
	++index;
}