#pragma once
#include <EngineCore/Actor.h>
#include "PreCompile.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>


#include <EnginePlatform/EngineInput.h>

// Ό³Έν :
class TitleLogo : public AActor
{
public:
	// constrcuter destructer
	TitleLogo();
	~TitleLogo();

	// delete Function
	TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator=(const TitleLogo& _Other) = delete;
	TitleLogo& operator=(TitleLogo&& _Other) noexcept = delete;

	void SetColImage(std::string_view _ColImageName);
protected:

private:
	//class UEngineWinImage* ColImage = nullptr;
};

