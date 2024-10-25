#pragma once
#include <Windows.h>

// 설명 :
class UEngineTimer
{
public:
	// constrcuter destructer
	UEngineTimer();
	~UEngineTimer();

	// delete Function
	UEngineTimer(const UEngineTimer& _Other) = delete;
	UEngineTimer(UEngineTimer&& _Other) noexcept = delete;
	UEngineTimer& operator=(const UEngineTimer& _Other) = delete;
	UEngineTimer& operator=(UEngineTimer&& _Other) noexcept = delete;

	void TimeCheckStart();

	// 나노 세컨드 이상
	double TimeCheck();

protected:

private:
	// 시간을 재는 방식은 일반적으로 카운팅이다.
	// 그런데 초당 100만을 재는 녀석이 있다고 치자.
	// int정도는 over해버린다.
	// 그래서 당연히 8바이트 정수가 필요하다.
	// 예전에는 

	//typedef union _LARGE_INTEGER {
	//	struct {
	//		DWORD LowPart;
	//		LONG HighPart;
	//	} DUMMYSTRUCTNAME;
	//	struct {
	//		DWORD LowPart;
	//		LONG HighPart;
	//	} u;
	//	LONGLONG QuadPart;
	//} LARGE_INTEGER;


	LARGE_INTEGER Int;

};

