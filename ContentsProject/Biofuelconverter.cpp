#include "PreCompile.h"
#include "Biofuelconverter.h"

ABiofuelconverter::ABiofuelconverter()
{
	Location.X = ScreenHX - 197;
	Location.Y = ScreenHY;

	{
		SpriteR = CreateDefaultSubObject<USpriteRenderer>();
		SpriteR->SetComponentCrate(SpriteR, "000_biofuel-converter.png", {}, { Location.X, Location.Y }, ERenderOrder::BUILDING);
		SpriteR->CreateAnimation("Idle", "Biofuelconverter", 0, 0, 1.0f);
	}

	{
		ModelAdd("001_biofuel-converter.png", 0, -2, 12);
		ModelAdd("002_biofuel-converter.png", -30, -20.5, 11);
		ModelAdd("002_biofuel-converter.png", 0, 32.5, 11);
		ModelAdd("002_biofuel-converter.png", 30, -20.5, 11);
		ModelAdd("003_biofuel-converter.png", -3, -2, 12);
	}
}

ABiofuelconverter::~ABiofuelconverter()
{
}


void ABiofuelconverter::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(NewPlayerState::Idle, std::bind(&ABiofuelconverter::Idle, this, std::placeholders::_1),
		[this]()
		{
			SpriteR->ChangeAnimation("Idle");
		}
	);

	FSM.ChangeState(NewPlayerState::Idle);
}

void ABiofuelconverter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//FSM.Update(_DeltaTime);
}

void ABiofuelconverter::Idle(float _DeltaTime)
{
}