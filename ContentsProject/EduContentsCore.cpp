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
	UEngineAPICore::GetCore()->CreateLevel("Title");
	UEngineAPICore::GetCore()->CreateLevel("Play");
}

void EduContentsCore::Tick()
{
}