#pragma once

// ���� :
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
	// �밡���� ǥ���
	// �̸��� �������
	// �ɹ������� �̸��� �빮��
	// ��������������
	// dujumsaigury
	// �����ǹ̷� ���ֽø� �˴ϴ�.
	// �Ǿո� 
	class AGameMode* GameMode = nullptr;
};