#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>

// Ό³Έν :
class AWindowTopBlack : public AActor
{
public:
	// constrcuter destructer
	AWindowTopBlack();
	~AWindowTopBlack();

	// delete Function
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

