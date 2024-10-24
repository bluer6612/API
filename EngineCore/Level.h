#pragma once

// 설명 :
class ULevel
{
public:
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	void BeginPlay()
	{

	}
	void Tick()
	{
	}

protected:

private:
	// 헝가리안 표기법
	// 이름은 마음대로
	// 맴버변수의 이름은 대문자
	// 음역하지마세요
	// dujumsaigury
	// 영어의미로 해주시면 됩니다.
	// 맨앞만 
	class AGameMode* GameMode = nullptr;
};