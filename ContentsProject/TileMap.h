#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineSerializer.h>

class Tile : public ISerializObject
{
public:
	USpriteRenderer* SpriteRenderer;

	bool IsMove = true;
	int TileType = -1;
	FVector2D Scale;
	FVector2D Pivot;
	int SpriteIndex;
	int TileIndex = 0;

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


class ATileMap : public AActor, public ISerializObject
{
public:
	ATileMap();
	~ATileMap();

	ATileMap(const ATileMap& _Other) = delete;
	ATileMap(ATileMap&& _Other) noexcept = delete;
	ATileMap& operator=(const ATileMap& _Other) = delete;
	ATileMap& operator=(ATileMap&& _Other) noexcept = delete;

	void Create(std::string_view _Sprite, FIntPoint _Count, FVector2D _TileSize);

	Tile* GetTileLocation(FVector2D _Location);

	FIntPoint GetIndex(FVector2D _Location);

	int GetTileIndex(FVector2D _Location);

	void SetTileSpriteIndex(FIntPoint _Index, int _SpriteIndex);
	void SetTileSpriteIndex(FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, FVector2D _Location, FVector2D _LocationPivot, int _SpriteIndex, int _TileIndex = 0, ERenderOrder _SpriteOrder = ERenderOrder::ZERO);

	Tile* GetTileRef(FIntPoint _Index);
	Tile* GetTileRef(FVector2D _Location);

	FVector2D IndexToTileLocation(FIntPoint _Index, FVector2D _Location);

	FIntPoint LocationToIndex(FVector2D _Location);

	bool IsIndexOver(FIntPoint _Index)  const;

	void Serialize(UEngineSerializer& _Ser);

	void DeSerialize(UEngineSerializer& _Ser);

	void SetCropsIndex(int _CropsIndex)
	{
		CropsIndex = _CropsIndex;
	}

	int GetCropsIndex() const
	{
		return CropsIndex;
	}

	void SetWater(int _Water)
	{
		Water = _Water;
	}

	int GetWater() const
	{
		return Water;
	}

	void SetGrow(int _Grow)
	{
		Grow = _Grow;
	}

	int GetGrow() const
	{
		return Grow;
	}

	void SetTime(int _Time)
	{
		Time = _Time;
	}

	int GetTime() const
	{
		return Time;
	}

protected:

private:
	FIntPoint TileCount;
	std::string SpriteName;
	FVector2D TileSize;
	std::vector<std::vector<Tile>> AllTiles;

	int CropsIndex = 0;
	int Water = 0;
	int Grow = 0;
	int Time = 0;
};


