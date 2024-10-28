#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"

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




	APlayMap* PMAP0 = GetWorld()->SpawnActor<APlayMap>();
	APlayMap* PMAP1 = GetWorld()->SpawnActor<APlayMap>();
	PMAP1->SetActorLocation({700, 200});
	APlayMap* PMAP2 = GetWorld()->SpawnActor<APlayMap>();
	PMAP2->SetActorLocation({ 500, 1000 });
	APlayMap* PMAP3 = GetWorld()->SpawnActor<APlayMap>();
	PMAP3->SetActorLocation({ 900, 600 });
}
