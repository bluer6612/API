#pragma once
#include "ActorComponent.h"

class USceneComponent : public UActorComponent

{
public:
	USceneComponent();
	~USceneComponent();

	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

	FTransform GetTransform() const
	{
		return Transform;
	}

	FTransform GetActorTransform();

	FVector2D GetComponentScale() const
	{
		return Transform.Scale;
	}

	FVector2D GetComponentLocation() const
	{
		return Transform.Location;
	}

	void SetComponentLocation(FVector2D _Location)
	{
		Transform.Location = _Location;
	}

	void SetComponentScale(FVector2D _Scale)
	{
		Transform.Scale = _Scale;
	}

	void SetComponentScaleOrigin()
	{
		Transform.Scale = { this->GetComponentScale().X, this->GetComponentScale().Y };
	}

	void SetAlphaChar(unsigned char _Value)
	{
		Alpha = _Value;
	}

	void SetAlphafloat(float _Value)
	{
		_Value = UEngineMath::Clamp(_Value, 0.0f, 1.0f);
		Alpha = static_cast<unsigned char>(_Value * 255.0f);
	}

protected:
	unsigned char Alpha = 255;

private:
	FTransform Transform;

};

