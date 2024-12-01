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
						Crops->SetTime(0);

						if (CropsNeedRegrow[Index] == Crops->GetGrow())
						{
							Crops->CropsReset(0, -1);
							CropsImage->SetActive(false);
						}
					}
					else if (0 == static_cast<int>(Crops->GetTime()) % (CropsNeedGrowTime[Index] / 6) && Progress != 5)
					{
						Crops->AddProgress();
						CropsImage->SetSprite("Crops.png", (4 + Progress) + 11 * Index);

						if (Progress == 6 / CropsNeedWater[Index] && 0 != Progress)
						{
							Crops->SetWaterNeed(true);
							UIManager->CroppatchTile->SetCropsTileSprite(CropsImage->GetComponentLocation(), 0);
						}
					}
				}
			}
		}
	}
}