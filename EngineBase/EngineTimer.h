#pragma once
#include <Windows.h>

// ���� :
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

	// ���� ������ �̻�
	double TimeCheck();

protected:

private:
	// �ð��� ��� ����� �Ϲ������� ī�����̴�.
	// �׷��� �ʴ� 100���� ��� �༮�� �ִٰ� ġ��.
	// int������ over�ع�����.
	// �׷��� �翬�� 8����Ʈ ������ �ʿ��ϴ�.
	// �������� 

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

