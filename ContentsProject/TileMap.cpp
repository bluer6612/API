#include "PreCompile.h"
#include "TileMap.h"

#include <EngineBase/EngineMath.h>

ATileMap::ATileMap()
{
}

ATileMap::~ATileMap()
{
}

void ATileMap::Create(std::string_view _Sprite, FIntPoint _Count, FVector2D _TileSize)
{
	SpriteName = _Sprite;
	TileCount = _Count;
	TileSize = _TileSize;

	AllTiles.resize(_Count.Y);

	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		AllTiles[y].resize(_Count.X);;
	}
}

FVector2D ATileMap::IndexToTileLocation(FIntPoint _Index, FVector2D _Location)
{
	return FVector2D(_Index.X * TileSize.X + _Index.X * _Location.X, _Index.Y * TileSize.Y + _Index.Y * _Location.Y);
}

FIntPoint ATileMap::LocationToIndex(const FVector2D _Location)
{
	FVector2D Location = _Location / TileSize;

	return FIntPoint(Location.iX(), Location.iY());
}

bool ATileMap::IsIndexOver(FIntPoint _Index) const
{
	if (0 > _Index.X)
	{
		return true;
	}

	if (0 > _Index.Y)
	{
		return true;
	}

	if (TileCount.X - 1 < _Index.X)
	{
		return true;
	}

	if (TileCount.Y - 1 < _Index.Y)
	{
		return true;
	}

	return false;
}

void ATileMap::SetTileSprite(FVector2D _Location, std::string_view _Sprite, int _SpriteIndex)
{
	//FIntPoint _Index = GetIndex(_Location);
	FIntPoint _Index = LocationToIndex(_Location);

	USpriteRenderer* FindSprite = AllTiles[_Index.X][_Index.Y].SpriteRenderer;
	FindSprite->SetSprite(_Sprite, _SpriteIndex);
}

void ATileMap::SetTileSpriteIndex(FIntPoint _Index, int _SpriteIndex)
{
	SetTileSpriteIndex(_Index, { 0,0 }, TileSize, { 0, 0 }, { 0,0 }, _SpriteIndex);
}

void ATileMap::SetTileSpriteIndex(FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, FVector2D _Location, FVector2D _LocationPivot, int _SpriteIndex, int _TileIndex, ERenderOrder _SpriteOrder)
{
	if (true == IsIndexOver(_Index))
	{
		return;
	}

	if (nullptr == AllTiles[_Index.Y][_Index.X].SpriteRenderer)
	{
		USpriteRenderer* NewSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		NewSpriteRenderer->SetComponentScale(TileSize);
		AllTiles[_Index.Y][_Index.X].SpriteRenderer = NewSpriteRenderer;
	}

	USpriteRenderer* FindSprite = AllTiles[_Index.Y][_Index.X].SpriteRenderer;
	FindSprite->SetSprite(SpriteName, _SpriteIndex);
	FindSprite->SetComponentScale(_SpriteScale);
	FindSprite->SetOrder(_SpriteOrder);
	if ("EmptyTile.png" == SpriteName)
	{
		FindSprite->SetAlphafloat(0.25f);
	}

	FVector2D TileLocation = IndexToTileLocation(_Index, _Location + _LocationPivot);

	AllTiles[_Index.Y][_Index.X].SpriteRenderer->SetComponentLocation(TileLocation + TileSize.Half() + _Pivot + _LocationPivot);
	AllTiles[_Index.Y][_Index.X].Pivot = _Pivot;
	AllTiles[_Index.Y][_Index.X].Scale = _SpriteScale;
	AllTiles[_Index.Y][_Index.X].SpriteIndex = _SpriteIndex;
	AllTiles[_Index.Y][_Index.X].TileIndex = _TileIndex;
}

FIntPoint ATileMap::GetIndex(FVector2D _Location)
{
	return LocationToIndex(_Location - GetActorLocation());
}

int ATileMap::GetTileIndex(FVector2D _Location)
{
	FIntPoint _Index = GetIndex(_Location);

	if (true == IsIndexOver(_Index))
	{
		return 0;
	}

	return AllTiles[_Index.Y][_Index.X].TileIndex;
}

Tile* ATileMap::GetTileLocation(FVector2D _Location)
{
	FVector2D TilePos = _Location - GetActorLocation();

	FIntPoint _Index = LocationToIndex(TilePos);

	if (true == IsIndexOver(_Index))
	{
		return nullptr;
	}

	return &AllTiles[_Index.Y][_Index.X];
}

Tile* ATileMap::GetTileRef(FVector2D _Location)
{
	FIntPoint Point = LocationToIndex(_Location);

	return GetTileRef(Point);
}

Tile* ATileMap::GetTileRef(FIntPoint _Index)
{
	if (true == IsIndexOver(_Index))
	{
		return nullptr;
	}

	return &AllTiles[_Index.Y][_Index.X];
}

void ATileMap::Serialize(UEngineSerializer& _Ser)
{
	_Ser << TileCount;
	_Ser << TileSize;
	_Ser << SpriteName;
	_Ser << AllTiles;
}

void ATileMap::DeSerialize(UEngineSerializer& _Ser)
{
	_Ser >> TileCount;
	_Ser >> TileSize;
	_Ser >> SpriteName;

	std::vector<std::vector<Tile>> LoadTiles;
	_Ser >> LoadTiles;

	Create(SpriteName, TileCount, TileSize);

	for (int y = 0; y < LoadTiles.size(); y++)
	{
		for (int x = 0; x < LoadTiles[y].size(); x++)
		{
			SetTileSpriteIndex({ x, y }, LoadTiles[y][x].Pivot, LoadTiles[y][x].Scale, { 0, 0 }, { 0,0 }, LoadTiles[y][x].SpriteIndex);
		}
	}
}