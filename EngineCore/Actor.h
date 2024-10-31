#pragma once
#include <EngineBase/Object.h>
#include <EngineBase/EngineMath.h>

#include "EngineSprite.h"

// 설명 :
class AActor : public UObject
{
public:
	typedef AActor Super;

	friend class ULevel;

	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	virtual void BeginPlay() {}
	// 델타타임이란 무엇인가?
	virtual void Tick(float _DeltaTime) {}

	class ULevel* GetWorld()
	{
		return World;
	}

	void SetActorLocation(FVector2D _Location)
	{
		Transform.Location = _Location;
	}

	void AddActorLocation(FVector2D _Direction)
	{
		Transform.Location += _Direction;
	}

	void SetActorScale(FVector2D _Scale)
	{
		Transform.Scale = _Scale;
	}

	FVector2D GetActorLocation()
	{
		return Transform.Location;
	}

	// 컴포넌트의 소유자는 액터 삭제도 액터가 해야한다.
	// 다른 클래스는 절대로 삭제하면 안된다.
	template<typename ComponentType>
	ComponentType* CreateDefaultSubObject()
	{
		ComponentType* NewComponent = new ComponentType();

		UActorComponent* ComponentPtr = dynamic_cast<UActorComponent*>(NewComponent);
		// 내가 널 만든 레벨이야.
		ComponentPtr->ParentActor = this;

		NewComponent->BeginPlay();
		Components.push_back(NewComponent);
		return NewComponent;
	}

protected:

private:
	class ULevel* World = nullptr;

	FTransform Transform;

	std::list<class UActorComponent*> Components;
};

