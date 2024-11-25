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

	void AddComponentLocation(FVector2D _Direction)
	{
		Transform.Location += _Direction;
	}

	void SetComponentScale(FVector2D _Scale)
	{
		Transform.Scale = _Scale;
	}

	void SetComponentScaleOrigin()
	{
		Transform.Scale = { this->GetComponentScale().X, this->GetComponentScale().Y };
	}

protected:

private:
	FTransform Transform;

};

