#include "PreCompile.h"
#include "EngineDirectory.h"

UEngineDirectory::UEngineDirectory()
	: UEnginePath()
{
	// 만들어지면 현재로 
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

	// 경로를 넣어주면 그 경로의 첫번째 파일을 가리키게 된다.
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(Path);


	while (false == Diriter._At_end())
	{
		std::filesystem::path File = *Diriter;
		Result.push_back(UEngineFile(File));
	}
	

}

