#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineSerializer.h>

enum class NewPlayerState
{
	Idle,
	Move,
};

class ACharacter : public ISerializObject
{
public:
	USpriteRenderer* SpriteRenderer;

	bool IsMove = true;
	int TileType = -1;
	FVector2D Scale;
	FVector2D Pivot;
	int SpriteIndex;

	void Serialize(UEngineSerializer& _Ser)
	{
		std::string SpriteName;
		if (nullptr != SpriteRenderer)
		{
			SpriteName = SpriteRenderer->GetCurSpriteName();
		}
		_Ser << SpriteName;
		_Ser << IsMove;
		_Ser << TileType;
		_Ser << Scale;
		_Ser << Pivot;
		_Ser << SpriteIndex;
	}

	void DeSerialize(UEngineSerializer& _Ser)
	{
		std::string SpriteName;
		_Ser >> SpriteName;
		_Ser >> IsMove;
		_Ser >> TileType;
		_Ser >> Scale;
		_Ser >> Pivot;
		_Ser >> SpriteIndex;

	}

};

class ACharacterMap : public AActor, public ISerializObject
{

public:
	ACharacterMap();
	~ACharacterMap();

	ACharacterMap(const ACharacterMap& _Other) = delete;
	ACharacterMap(ACharacterMap&& _Other) noexcept = delete;
	ACharacterMap& operator=(const ACharacterMap& _Other) = delete;
	ACharacterMap& operator=(ACharacterMap&& _Other) noexcept = delete;


	void Create(std::string_view _Sprite, FIntPoint _Count, FVector2D _ACharacterMapSize);

	void SetACharacterMapIndex(FIntPoint _Index, int _SpriteIndex);
	void SetACharacterMapIndex(FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex);

	FVector2D IndexToACharacterMapLocation(FIntPoint _Index);

	bool IsIndexOver(FIntPoint _Index);

protected:

private:
	FIntPoint ACharacterMapCount;
	FVector2D ACharacterMapSize;
	std::string SpriteName;
	std::vector<std::vector<ACharacter>> AllACharacterMaps;
};