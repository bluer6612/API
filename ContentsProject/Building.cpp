#include "PreCompile.h"
#include "Building.h"

ABuilding::ABuilding()
{
}

ABuilding::~ABuilding()
{
}

void ABuilding::ModelAdd(std::string _Name, int _SizeX, int _SizeY, int _X, int _Y, int _Order)
{
	Model[index] = CreateDefaultSubObject<USpriteRenderer>();
	Model[index]->SetSprite(_Name);
	Model[index]->SetComponentScale({ static_cast<float>(_SizeX * 2), static_cast<float>(_SizeY * 2) });
	Model[index]->SetComponentLocation({ static_cast<float>(Location.X + _X), static_cast<float>(Location.Y + _Y) });
	Model[index]->SetOrder(_Order);
	++index;
}

void ABuilding::ModelAdd(std::string _Name, int _ModelNumber, int _SizeX, int _SizeY, int _X, int _Y, int _Order)
{
	Model[index] = CreateDefaultSubObject<USpriteRenderer>();
	Model[index]->SetSprite(_Name);
	Model[index]->CreateAnimation("Idle", _Name, _ModelNumber, _ModelNumber, 0);
	Model[index]->SetComponentScale({ static_cast<float>(_SizeX * 2), static_cast<float>(_SizeY * 2) });
	Model[index]->SetComponentLocation({ static_cast<float>(Location.X + _X), static_cast<float>(Location.Y + _Y) });
	Model[index]->SetOrder(_Order);
	++index;
}