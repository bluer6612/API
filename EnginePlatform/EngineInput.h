#pragma once
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

#include <vector>
#include <functional>

// �̱����� ����

// ������ ������ �����Ҷ� 4���� �η��� �������.
// ��������, xx����, xx����, ��������
// ���������� �̱����� �����Ҷ� ������ ���� �������.
// �̱����̶� ��ü�� ���α׷��� ��Ʋ� ���� 1���̻� ������ ���ϰ� �ϱ� ���� �����̴�.
// �� �̰� �̿��� 

// �̱��� �Ҷ� �ϸ� �ȵǴ� �� 
// 1. ���� ���ϰ� �����Ϸ��� �̱����� ��� => �ȵ���.

// 1. �����ڸ� private���� �����ϴ�.

// � Ŭ������ �������. 
// EngineWindow�� �����غ���. 
// ���⿡�� �̱����� �����ϰڴ�.
// ���� : 

enum class KeyEvent
{
	Down,
	Press,
	Free,
	Up,
};

class UEngineInput
{
public:
	// constrcuter destructer
	~UEngineInput();

	// delete Function
	UEngineInput(const UEngineInput& _Other) = delete;
	UEngineInput(UEngineInput&& _Other) noexcept = delete;
	UEngineInput& operator=(const UEngineInput& _Other) = delete;
	UEngineInput& operator=(UEngineInput&& _Other) noexcept = delete;

	// static�� �Բ��ϰ� �Ǵ� ��찡 ����.
	// �� Ŭ���� �ڱ��ڽ��� ���� �ܺο� �����Ѵ�.
	// ���⿡�� �������� ������ �����µ�.

	// ũ�� ���������� �������� ������.

	static UEngineInput& GetInst()
	{
		// ���� static�� ��ȣ�Ѵ�.
		// �ڵ尡 ª������ �����Ѵ�.
		// Ŭ���� ������ static�� 
		// �ܺο� �����ϱⰡ ��ٷӴ�.

		// ���� �̱����� ����Ⱑ ����.
		static UEngineInput Inst = UEngineInput();
		return Inst;
	}


	//static UEngineInput& GetInst()
	//{
	//	return Inst;
	//}

	// ���������� ������ �� 1���̴�.
	// if �־ �Ȱ�.
	// ����� �ִٴ°� �����ε�.
	// �׷��� �Ⱦ��Ѵ�.
	//static UEngineInput& GetInst()
	//{
	//	if (nullptr == Inst)
	//	{
	//		Inst = new UEngineInput();
	//	}
	//	return *Inst;
	//}

	// �ѽ��� �����Լ��� ������ �������� �Ѵ�.
	// ��𼱰� ������ ȣ������� �Ѵ�.
	//static void DestroyInst()
	//{
	//	if (nullptr != Inst)
	//	{
	//		delete Inst;
	//		Inst = nullptr;
	//	}
	//}

	// �ܺο� �����ϱ�� �ȴ�.
private:
	class UEngineKey
	{
	public:
		int Key = -1;

		// Ű�� �ȴ����ٰ� ó�� ��������
		bool IsDown = false;

		// Ű�� ���� ���ķ� ��� ������ ������
		bool IsPress = false;

		// Ű�� �����ٰ� ������
		bool IsUp = false;

		// Ű�� �ȴ����� ������
		bool IsFree = true;

		float PressTime = 0.0f;

		std::vector<std::function<void()>> PressEvents;
		std::vector<std::function<void()>> DownEvents;
		std::vector<std::function<void()>> UpEvents;
		std::vector<std::function<void()>> FreeEvents;


		// ���ͳ� ����Ʈ�� ����ϸ� ������ ����.
		// �л����� ��ó�� ���ϴµ�
		// �ᱹ ������ �ö󰡸� �˴ϴ�.

		UEngineKey()
		{
		}

		UEngineKey(int _Key)
			: Key(_Key)
		{
		}

		void EventCheck();

		void KeyCheck(float _DeltaTime);
		
	};


public:
	void KeyCheck(float _DeltaTime);
	void EventCheck(float _DeltaTime);

	// UEngineInput::GetInst().IsDown('A')

	bool IsDown(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}

		// 
		// Keys[_KeyIndex] => ������ ���ο��� ��带 �����.
		// UMapNode
		// {
		//     UEngineKey Value = UEngineKey();
		// }

		return Keys[_KeyIndex].IsDown;
	}

	bool IsUp(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}

		return Keys[_KeyIndex].IsUp;
	}

	bool IsPress(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}

		return Keys[_KeyIndex].IsPress;
	}

	float IsPressTime(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}

		return Keys[_KeyIndex].PressTime;
	}


	bool IsFree(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}

		return Keys[_KeyIndex].IsFree;
	}

	void BindAction(int _KeyIndex, KeyEvent _EventType,  std::function<void()> _Function);

protected:

private:
	// �̷��� ����
	// static ���� ���� �����ϰ� 
	// �����ʿ� ����.
	// static UEngineInput Inst;
	
	// ��������
	// static UEngineInput* Inst;

	// �̱����� ����
	// �̱��� ����� 1
	// 1. �����ڸ� private���� �����ϴ�.

	// 100�������� 
	std::map<int, UEngineKey> Keys;

	UEngineInput();

};
