#include "PreCompile.h"
#include "FarmingManager.h"
#include <EngineCore/GlobalVariable.h>

AFarmingManager::AFarmingManager()
{
}

AFarmingManager::~AFarmingManager()
{
}

void AFarmingManager::BeginPlay()
{
	Super::BeginPlay();
}

void AFarmingManager::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	GrowTime += _DeltaTime;

	if (1.0f <= GrowTime)
	{
		GrowTime -= 1.0f;

		if (0 < UIManager->CropsAllVector.size())
		{
			for (int i = 0; i < UIManager->CropsAllVector.size(); i++)
			{
				Tile* Crops = UIManager->CropsAllVector[i];

				USpriteRenderer* CropsImage = UIManager->CroppatchTileImage[Crops->GetCropTileIndex()];

				if (false == Crops->GetWaterNeed())
				{
					int Index = Crops->GetCropsIndex();
					int Progress = Crops->GetProgress();

					Crops->AddTime(1.0f);

					if (CropsNeedGrowTime[Index] <= Crops->GetTime())
					{
						Money += CropsSellMoney[Index];

						Crops->SetTime(0);

						if (CropsNeedRegrow[Index] > Crops->GetGrow())
						{
							Crops->AddGrow();
							Crops->SetProgress(0);
							Crops->SetWater(0);
							Crops->SetWaterNeed(true);
							UIManager->CroppatchTile->SetCropsTileSprite(CropsImage->GetComponentLocation(), 0);
							
							CropsImage->SetSprite("Crops.png", (3 + Crops->GetProgress()) + 11 * Index);
						}
						else
						{
							CropsImage->SetSprite("gridsmall.png");
							CropsImage->SetAlphafloat(0.75f);
							CropsImage->SetActive(false);

							Crops->CropsReset(0, -1);
						}
					}
					else if (1 + Progress <= Crops->GetTime() / (6 * (1 + Progress)))
					{
						Crops->AddProgress();
						CropsImage->SetSprite("Crops.png", (3 + Progress) + 11 * Index);

						if (0 == Progress % CropsNeedWater[Index] && 0 != Progress)
						{
							Crops->SetWaterNeed(true);
							UIManager->CroppatchTile->SetCropsTileSprite(CropsImage->GetComponentLocation(), 0);
						}
					}
				}
			}
		}
	}
	//AUIManager::CroppatchTile;

}