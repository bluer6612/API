#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"
#include "Player.h"
#include "ANewPlayer.h"
#include "Score.h"

#include "ContentsEnum.h"

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

// �𸮾󿡼��� MainPawn ���ΰ� ������ �����ϰ� �ؿ�.
void APlayGameMode::BeginPlay()
{
	// �𸮾󿡼� ���� ���� 
	// ���� ��Ģ�� ���ϰ� ���ӿ� ���� ��Ģ�� �԰��� �غ��϶�� �𸮾��� �غ���
	// ���� ���� ��������ٴ� �� �� ��ü�� �߿��ϴ�.
	// ���� ��ü�� �غ��ų�� �ִ� �����̴�.
	
	// ���� ���� �������� ���Ӹ��
	// => ������ ��������� ������ ��������� �Ѵ�.
	// �������� �������� �Ұ��̴�.

	// �������� ������� ���Ӹ�忡��
	// BeginPlay�� �Ҷ� => �� ������ ���۵Ǹ� �����ؾ� �ϴ� ����
	// �÷��̾�� ���״�� �ֿ� ���� ���Ͷ�� �����ϰ� �ֱ� ������.
	// ������ ��������� ����������� ���͵��� ����� �뵵�� �������� �ʾ�.

	// GameMode =>�� ��ӹ޴� ���� ���� ���Ӹ�����
	// ������ �����Ҵ� �ʿ��� �͵��� �غ��϶�� ������� ���� ���� ���������
	// <= �ظ��ϸ� �ʹݿ� �� ����� ����.

	ANewPlayer* Player = GetWorld()->GetPawn<ANewPlayer>();
	Player->SetColImage("bg001_Col.png");

	int a = 0;

	{
		AScore* NewActor = GetWorld()->SpawnActor<AScore>();

		NewActor->SetActorLocation({30, 30});
		NewActor->SetTextSpriteName("Text.bmp");
		NewActor->SetOrder(ERenderOrder::UI);
		NewActor->SetTextScale({5, 10});
		NewActor->SetValue(45362784);

	}
}
