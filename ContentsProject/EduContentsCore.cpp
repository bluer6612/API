#include "PreCompile.h"
#include "EduContentsCore.h"
#include <EngineCore/EngineAPICore.h>

EduContentsCore::EduContentsCore()
{
}

EduContentsCore::~EduContentsCore()
{
}

// ������ ����ǰ� �� 1�� ����ȴ�.
void EduContentsCore::BeginPlay()
{
	// �ƹ� ���� ���� �ڵ�.
	// �ִ� �Ե��� ��������Ѵ�.
	// TitleLevel = new ULevel();
	
	// ��ü�� �����ϴ� �Լ��� �������ִµ� �����ϸ� �ȵȴٴ°�.
	// �̰� ���ؼ� �ȸ��� �ֵ� => �� �ƹ��� ���� ���� ���ɼ��� ����.
	
	UEngineAPICore::GetCore()->CreateLevel("Title");
	UEngineAPICore::GetCore()->CreateLevel("Play");
	UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->ChangeLevel("End");

}

void EduContentsCore::Tick()
{
}