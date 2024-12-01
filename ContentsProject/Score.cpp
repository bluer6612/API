#include "PreCompile.h"
#include "Score.h"

AScore::AScore()
{
	for (size_t i = 0; i < 12; i++)
	{
		USpriteRenderer* Sprite = CreateDefaultSubObject<USpriteRenderer>();
		Sprite->SetCameraEffect(false);
		Renders.push_back(Sprite);
	}
}

AScore::~AScore()
{
}

void AScore::BeginPlay()
{
}

void AScore::Tick(float _DeltaTime)
{
}

void AScore::SetTextSpriteName(const std::string _Text)
{
	TextSpriteName = _Text;

	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetSprite(TextSpriteName);
	}
}

void AScore::SetOrder(int _Order)
{
	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetOrder(_Order);
	}
}

void AScore::SetActive(bool _Bool)
{
	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetActive(_Bool);
	}
}

void AScore::SetValue(int _Score, bool _Order)
{
	std::string Number = std::to_string(_Score);

	if (Renders.size() <= Number.size())
	{
		MSGASSERT("자리수를 넘겼습니다.");
		return;
	}

	FVector2D Pos = FVector2D::ZERO;

	if (false == _Order)
	{
		for (size_t i = 0; i < Number.size(); i++)
		{
			char Value = Number[i] - '0';
			Renders[i]->SetSprite(TextSpriteName, Value);
			Renders[i]->SetComponentScale(TextScale);
			Renders[i]->SetComponentLocation(Pos);
			Pos.X += TextScale.X + 1;
			Renders[i]->SetActive(true);
		}
	}
	else
	{
		for (size_t i = 0; i < Number.size(); i++)
		{
			char Value = Number[i] - '0';
			Renders[i]->SetSprite(TextSpriteName, Value);
			Renders[i]->SetComponentScale(TextScale);
			Renders[i]->SetComponentLocation(Pos);
			Pos.X += TextScale.X - 15;
			Renders[i]->SetActive(true);
		}
	}

	for (size_t i = Number.size(); i < Renders.size(); i++)
	{
		Renders[i]->SetActive(false);
	}
}