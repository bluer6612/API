#include "PreCompile.h"
#include "CharacterMap.h"

ACharacterMap::ACharacterMap()
{
}

ACharacterMap::~ACharacterMap()
{
}

void ACharacterMap::Create(std::string_view _Sprite, FIntPoint _Count, FVector2D _ACharacterMapSize)
{
	SpriteName = _Sprite;
	ACharacterMapSize = _ACharacterMapSize;
	ACharacterMapCount = _Count;

	AllACharacterMaps.resize(_Count.Y);

	for (size_t y = 0; y < AllACharacterMaps.size(); y++)
	{
		AllACharacterMaps[y].resize(_Count.X);;
	}
}

bool ACharacterMap::IsIndexOver(FIntPoint _Index)
{
	if (0 > _Index.X)
	{
		return true;
	}

	if (0 > _Index.Y)
	{
		return true;
	}

	if (ACharacterMapCount.X - 1 < _Index.X)
	{
		return true;
	}

	if (ACharacterMapCount.Y - 1 < _Index.Y)
	{
		return true;
	}

	return false;
}

FVector2D ACharacterMap::IndexToACharacterMapLocation(FIntPoint _Index)
{
	return FVector2D(_Index.X * ACharacterMapSize.X, _Index.Y * ACharacterMapSize.Y);
}


void ACharacterMap::SetACharacterMapIndex(FIntPoint _Index, int _SpriteIndex)
{
	SetACharacterMapIndex(_Index, { 0,0 }, ACharacterMapSize, _SpriteIndex);
}

void ACharacterMap::SetACharacterMapIndex(FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex)
{
	if (true == IsIndexOver(_Index))
	{
		return;
	}

	if (nullptr == AllACharacterMaps[_Index.Y][_Index.X].SpriteRenderer)
	{
		USpriteRenderer* NewSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		NewSpriteRenderer->SetComponentScale(ACharacterMapSize);
		AllACharacterMaps[_Index.Y][_Index.X].SpriteRenderer = NewSpriteRenderer;
	}


	USpriteRenderer* FindSprite = AllACharacterMaps[_Index.Y][_Index.X].SpriteRenderer;
	FindSprite->SetSprite(SpriteName, _SpriteIndex);

	FVector2D ACharacterMapLocation = IndexToACharacterMapLocation(_Index);
	FindSprite->SetComponentScale(_SpriteScale);
	FindSprite->SetOrder(_Index.Y);

	AllACharacterMaps[_Index.Y][_Index.X].SpriteRenderer->SetComponentLocation(ACharacterMapLocation + ACharacterMapSize.Half() + _Pivot);
	AllACharacterMaps[_Index.Y][_Index.X].Pivot = _Pivot;
	AllACharacterMaps[_Index.Y][_Index.X].Scale = _SpriteScale;
	AllACharacterMaps[_Index.Y][_Index.X].SpriteIndex = _SpriteIndex;
}