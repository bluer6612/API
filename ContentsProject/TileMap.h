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

	void SetLocation(FVector2D _Location)
	{
		Location = _Location;
	}

	FVector2D GetLocation() const
	{
		return Location;
	}

	void CropsReset(int _CropTileIndex, int _CropsIndex)
	{
		this->SetCropTileIndex(_CropTileIndex);
		this->SetCropsIndex(_CropsIndex);
		this->SetGrow(0);
		this->SetWater(0);
		this->SetProgress(0);
		this->SetTime(0);
		this->SetWaterNeed(true);
	}

	void SetCropTileIndex(int _CropTileIndex)
	{
		CropTileIndex = _CropTileIndex;
	}

	int GetCropTileIndex() const
	{
		return CropTileIndex;
	}

	void SetCropsIndex(int _CropsIndex)
	{
		CropsIndex = _CropsIndex;
	}

	int GetCropsIndex() const
	{
		return CropsIndex;
	}

	void AddWater()
	{
		Water += 1;
	}

	void SetWater(int _Water)
	{
		Water = _Water;
	}

	int GetWater() const
	{
		return Water;
	}

	void AddGrow()
	{
		Grow += 1;
	}

	void SetGrow(int _Grow)
	{
		Grow = _Grow;
	}

	int GetGrow() const
	{
		return Grow;
	}

	void AddProgress()
	{
		Progress += 1;
	}

	void SetProgress(int _Progress)
	{
		Progress = _Progress;
	}

	int GetProgress() const
	{
		return Progress;
	}

	void AddTime(float _Time)
	{
		Time += _Time;
	}

	void SetTime(float _Time)
	{
		Time = _Time;
	}

	float GetTime() const
	{
		return Time;
	}

	void SetWaterNeed(bool _WaterNeed)
	{
		WaterNeed = _WaterNeed;
	}

	bool GetWaterNeed() const
	{
		return WaterNeed;
	}

private:
	FVector2D Location = {};
	int CropTileIndex = 0;
	int CropsIndex = 0;
	int Water = 0;
	int Grow = 0;
	int Progress = 0;
	float Time = 0;
	bool WaterNeed = true;
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

	Tile* GetTileByLocation(FVector2D _Location);

	FIntPoint GetIndex(FVector2D _Location);

	int GetTileIndex(FVector2D _Location);

	void SetCropsTileSprite(FVector2D _Location, int _SpriteIndex);

	void SetTileSpriteIndex(FIntPoint _Index, int _SpriteIndex);
	void SetTileSpriteIndex(FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex, int _TileIndex = 0, ERenderOrder _SpriteOrder = ERenderOrder::ZERO);

	Tile* GetTileRef(FIntPoint _Index);
	Tile* GetTileRef(FVector2D _Location);

	FVector2D IndexToTileLocation(FIntPoint _Index);

	FIntPoint LocationToIndex(FVector2D _Location);

	bool IsIndexOver(FIntPoint _Index)  const;

	void Serialize(UEngineSerializer& _Ser);

	void DeSerialize(UEngineSerializer& _Ser);

protected:

private:
	FIntPoint TileCount;
	std::string SpriteName;
	FVector2D TileSize;
	std::vector<std::vector<Tile>> AllTiles;
};


