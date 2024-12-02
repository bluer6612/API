#pragma once
#include <vector>

#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>

class AScore : public AActor
{
public:
	
	AScore();
	~AScore();

	
	AScore(const AScore& _Other) = delete;
	AScore(AScore&& _Other) noexcept = delete;
	AScore& operator=(const AScore& _Other) = delete;
	AScore& operator=(AScore&& _Other) noexcept = delete;

	void SetTextSpriteName(const std::string _Text);

	void SetTextScale(FVector2D _TextScale)
	{
		TextScale = _TextScale;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);

	void SetLocation(FVector2D _Pos);

	void SetActive(int _Score, bool _Active);

	void SetValue(int _Score, int _Order = 0, bool _Active = true);

	int GetValue(int _Score);

	int ValueData = 0;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::string TextSpriteName;
	FVector2D TextScale;
	std::vector<class USpriteRenderer*> Renders;
};

