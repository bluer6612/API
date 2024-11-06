#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>

// 명확히 하라.
// 점프내부에서는 점프와 관련된 코드만 실행하라.
enum class PlayerState
{
	Idle,
	Move,
	Jump,
};

// 설명 :
class APlayer : public AActor
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	//void MoveFunction(FVector2D _Dir);

	/*void LeftMove();
	void RightMove();
	void UpMove();
	void DownMove();*/

	void RunSoundPlay();

	void LevelChangeStart();
	void LevelChangeEnd();

	void SetColImage(std::string_view _ColImageName);

protected:

private:

	float Speed = 500.0f;
	int MySpriteIndex = 0;

	class USpriteRenderer* SpriteRenderer;
	// class std::vector< USpriteRenderer* LeftRenderer;

	class UEngineWinImage* ColImage = nullptr;

	PlayerState CurPlayerState = PlayerState::Idle;

	// 점프
	// 공격
	// 점프공격
	// 

	void ChangeState(PlayerState CurPlayerState);

	void IdleStart();
	void Idle(float _DeltaTime);
	void MoveStart();
	void Move(float _DeltaTime);
	//void Fly(float _DeltaTime);

	// 상태는 아니지만 도움이나 체크에 처리되는 함수
	void Gravity()
	{

	}


	// void Jump();

};

