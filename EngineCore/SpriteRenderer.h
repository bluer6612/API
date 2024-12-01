#pragma once
#include "SceneComponent.h"
#include "EngineSprite.h"

#include <map>
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineMath.h>
#include <ContentsProject/ContentsEnum.h>

enum class PivotType
{
	Center,
	Left,
	Bot,
	Top,
	LeftTop,
};

class USpriteRenderer : public USceneComponent
{
public:
	class FrameAnimation
	{
	public:
		UEngineSprite* Sprite = nullptr;
		std::vector<int> FrameIndex;
		std::vector<float> FrameTime;
		std::map<int, EngineDelegate> Events;

		int CurIndex = 0;
		int ResultIndex = 0;
		float CurTime = 0.0f;
		bool Loop = true;
		bool IsEnd = false;

		void Reset()
		{
			CurIndex = 0;
			CurTime = 0;
			ResultIndex = 0;
			IsEnd = false;
		}
	};


public:
	USpriteRenderer();
	~USpriteRenderer();

	USpriteRenderer(const USpriteRenderer& _Other) = delete;
	USpriteRenderer(USpriteRenderer&& _Other) noexcept = delete;
	USpriteRenderer& operator=(const USpriteRenderer& _Other) = delete;
	USpriteRenderer& operator=(USpriteRenderer&& _Other) noexcept = delete;

	void Render(float _DeltaTime);
	void BeginPlay() override;
	void ComponentTick(float _DeltaTime) override;

	void SetSprite(std::string_view _Name, int _CurIndex = 0);

	FVector2D SetSpriteScale(float _Ratio = 2.0f, int _CurIndex = 0);

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);

	int GetOrder() const
	{
		return Order;
	}

	void SetComponentCrate(USpriteRenderer* _SR, std::string_view _Model, FVector2D _Scale, FVector2D _Location, ERenderOrder _Order);

	void SetComponentCrate(USpriteRenderer* _SR, std::string_view _Model, int _index, FVector2D _Scale, FVector2D _Location, ERenderOrder _Order);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, int _Start, int _End, float Time = 0.1f, bool _Loop = true);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop = true);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, float _Frame, bool _Loop = true);

	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false);

	void SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function);

	std::string GetCurSpriteName()
	{
		return Sprite->GetName();
	}

	void SetCameraEffect(bool _Value)
	{
		IsCameraEffect = _Value;
	}

	void SetPivotValue(FVector2D _Value);

	void SetPivotType(PivotType _Type);

	void SetCameraEffectScale(float _Effect);

	bool IsCurAnimationEnd()
	{
		return CurAnimation->IsEnd;
	}

	void SetAlphaChar(unsigned char _Value)
	{
		Alpha = _Value;
	}
	void SetAnimationSpeed(float _Speed)
	{
		CurAnimationSpeed = _Speed;
	}

	void ResetAnimationSpeed()
	{
		CurAnimationSpeed = 1.0f;
	}

	void SetAlphafloat(float _Value)
	{
		_Value = UEngineMath::Clamp(_Value, 0.0f, 1.0f);

		Alpha = static_cast<unsigned char>(_Value * 255.0f);
	}

	void SetCount(int _Count)
	{
		Count = _Count;
	}

	int GetCount() const
	{
		return Count;
	}

protected:

private:
	int Count = 0;
	int Order = 0;
	int CurIndex = 0;

	bool IsCameraEffect = true;
	float CameraEffectScale = 1.0f;
	float CurAnimationSpeed = 1.0f;

	unsigned char Alpha = 255;
	FVector2D Pivot = FVector2D(0.5f, 0.5f);

	class UEngineSprite* Sprite = nullptr;

	std::map<std::string, FrameAnimation> FrameAnimations;
	FrameAnimation* CurAnimation = nullptr;
};