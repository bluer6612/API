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
	AUIManager* UIManager = nullptr;
	{
		UIManager = GetWorld()->SpawnActor<AUIManager>();

		this->SetUIManager(UIManager);
	}
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
				ATileMap* Crops = UIManager->CropsAllVector[i];
				int Index = Crops->GetCropsIndex();

				USpriteRenderer* CropsImage = UIManager->CroppatchTileImage[Crops->GetTileIndex()];

				Crops->AddTime(1.0f);

				if (CropsNeedGrowTime[Index] <= Crops->GetTime())
				{
					Money += CropsSellMoney[Index];

					if (CropsNeedRegrow[Index] > Crops->GetGrow())
					{
						Crops->AddGrow();
						Crops->SetProgress(0);
						Crops->SetWater(0);
						CropsImage->SetSprite("Crops.png", (3 + Crops->GetProgress()) + 11 * Index);
					}
					else
					{
						CropsImage->SetActive(false);
						Crops->CropsReset(0, 0);

						delete Crops;
						Crops = nullptr;
					}
				}
				else if (1 <= Crops->GetTime() / (6 - Crops->GetProgress()))
				{
					Crops->AddProgress();
					CropsImage->SetSprite("Crops.png", (3 + Crops->GetProgress()) + 11 * Index);
				}
			}
		}
	}
	//AUIManager::CroppatchTile;

}