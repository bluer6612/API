#include "PreCompile.h"
#include "EngineDirectory.h"

UEngineDirectory::UEngineDirectory()
	: UEnginePath()
{
	// ��������� ����� 
}

UEngineDirectory::UEngineDirectory(std::string_view _Path)
	: UEnginePath(_Path)
{

}


UEngineDirectory::~UEngineDirectory()
{
}


std::vector<class UEngineFile> UEngineDirectory::GetAllFile()
{
	std::vector<class UEngineFile> Result;

	// ��θ� �־��ָ� �� ����� ù��° ������ ����Ű�� �ȴ�.
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(Path);


	while (false == Diriter._At_end())
	{
		std::filesystem::path File = *Diriter;
		Result.push_back(UEngineFile(File));
	}
	

}

