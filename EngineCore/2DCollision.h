#pragma once
#include "SceneComponent.h"
#include <set>

class U2DCollision : public USceneComponent
{
public:
	friend class ULevel;

	U2DCollision();
	~U2DCollision();

	U2DCollision(const U2DCollision& _Other) = delete;
	U2DCollision(U2DCollision&& _Other) noexcept = delete;
	U2DCollision& operator=(const U2DCollision& _Other) = delete;
	U2DCollision& operator=(U2DCollision&& _Other) noexcept = delete;

	void BeginPlay() override;

	void ComponentTick(float _DeltaTime) override;

	template<typename EnumType>
	EnumType GetGroup() const
	{
		return static_cast<EnumType>(CollisionGroup);
	}

	int GetGroup() const
	{
		return CollisionGroup;
	}

	template<typename EnumType>
	void SetCollisionGroup(EnumType _CollisionGroup)
	{
		SetCollisionGroup(static_cast<int>(_CollisionGroup));
	}

	void SetCollisionGroup(int _CollisionGroup)
	{
		CollisionGroup = _CollisionGroup;
	}

	template<typename EnumType>
	AActor* CollisionOnce(EnumType _OtherCollisionGroup, FVector2D _NextPos = FVector2D::ZERO)
	{
		// 상대가 100개이다. 100개 
		std::vector<AActor*> Result;
		Collision(static_cast<int>(_OtherCollisionGroup), Result, _NextPos, 1);

		if (true == Result.empty())
		{
			return nullptr;
		}

		return Result[0];
	}

	template<typename EnumType>
	std::vector<AActor*> CollisionAll(EnumType _OtherCollisionGroup, FVector2D _NextDir)
	{
		// 상대가 100개이다. 100개 
		std::vector<AActor*> Result;
		Collision(static_cast<int>(_OtherCollisionGroup), Result, _NextDir, -1);

		return Result;
	}

	bool Collision(int _OtherCollisionGroup, std::vector<AActor*>& _Result, FVector2D _NextDir, unsigned int  _Limite);

	void SetCollisionType(ECollisionType _CollisionType)
	{
		CollisionType = _CollisionType;
	}

	ECollisionType GetCollisionType() const
	{
		return CollisionType;
	}

	void SetCameraEffect(bool _IsCameraEffect)
	{
		IsCameraEffect = _IsCameraEffect;
	}

	//                                        충돌한 상대
	void SetCollisionEnter(std::function<void(AActor*)> _Function);
	void SetCollisionStay(std::function<void(AActor*)> _Function);
	void SetCollisionEnd(std::function<void(AActor*)> _Function);

protected:

private:
	void CollisionEventCheck(class U2DCollision* _Other);

	// 충돌체의 오더는 약간 의미가 다르다.
	// -1 충돌 그룹을 지정해주지 않았다
	// -1 은 사용하면 안된다.
	// 양수만 된다.
	ECollisionType CollisionType = ECollisionType::CirCle;
	int CollisionGroup = -1;

	// value없는 맵입니다.
	std::set<U2DCollision*> CollisionCheckSet;

	bool IsCameraEffect = true;

	std::function<void(AActor*)> Enter;
	std::function<void(AActor*)> Stay;
	std::function<void(AActor*)> End;
};

// 여러분들이 만들어야 하는 기능
// enum class ContentsCollision
// {
//     PlayerBody,
//     PlayerAttack,
//	   MonsterBody,
//     MonsterAttack,
// }

// 대부분의 충돌 함수들이 이와 같은 엮어주는 함수를 지원하거나 
// 엔진수준의 GUI로 지원해 줘야 합니다.
// void SetCollisionGroupCheck(ContentsCollision::PlayerBody, ContentsCollision::MonsterAttack);
