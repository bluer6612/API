#pragma once
#include "SceneComponent.h"

// 설명 :
class U2DCollision : public USceneComponent
{
public:
	// constrcuter destructer
	U2DCollision();
	~U2DCollision();

	// delete Function
	U2DCollision(const U2DCollision& _Other) = delete;
	U2DCollision(U2DCollision&& _Other) noexcept = delete;
	U2DCollision& operator=(const U2DCollision& _Other) = delete;
	U2DCollision& operator=(U2DCollision&& _Other) noexcept = delete;

	void BeginPlay() override;

	void ComponentTick(float _DeltaTime) override;

	template<typename EnumType>
	EnumType GetGroup()
	{
		return static_cast<EnumType>(CollisionGroup);
	}

	int GetGroup()
	{
		return CollisionGroup;
	}

	// 충돌체에게 충돌그룹을 지정안해주는건 의미가 없다.
	// 중간에 충돌 그룹이 바뀌어야 되면 이야기 부탁.
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
	bool IsCollision(EnumType _OtherCollisionGroup)
	{
		return IsCollision(static_cast<int>(_OtherCollisionGroup));
	}

	template<typename EnumType>
	U2DCollision* CollisionOnce(EnumType _OtherCollisionGroup)
	{
		return CollisionOnce(static_cast<int>(_OtherCollisionGroup));
	}

	template<typename EnumType>
	bool Collision(EnumType _OtherCollisionGroup, std::vector<U2DCollision*>* _Result = nullptr)
	{
		return Collision(static_cast<int>(_OtherCollisionGroup), _Result);
	}

	bool IsCollision(int _OtherCollisionGroup);
	U2DCollision* Collision(int _OtherCollisionGroup);
	// 이거쓰면 다되죠.
	bool Collision(int _OtherCollisionGroup, std::vector<U2DCollision*>* _Result = nullptr);


protected:

private:
	// 충돌체의 오더는 약간 의미가 다르다.
	// -1 충돌 그룹을 지정해주지 않았다
	// -1 은 사용하면 안된다.
	// 양수만 된다.
	int CollisionGroup = -1;
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

