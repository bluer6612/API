#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>

class AWindowTopBlack : public AActor
{
public:
		AWindowTopBlack();
	~AWindowTopBlack();

		AWindowTopBlack(const AWindowTopBlack& _Other) = delete;
	AWindowTopBlack(AWindowTopBlack&& _Other) noexcept = delete;
	AWindowTopBlack& operator=(const AWindowTopBlack& _Other) = delete;
	AWindowTopBlack& operator=(AWindowTopBlack&& _Other) noexcept = delete;

	void BeginPlay() override;

	void LevelChangeStart() override;

	void SetColImage(std::string_view _ColImageName);
protected:

private:
	class UEngineWinImage* ColImage = nullptr;
	class USpriteRenderer* SpriteRenderer = nullptr;
};

