#pragma once

static const int CropsCount = 44;
static const int MenuCountY = 4;

// ���� :
class UGlobalVariable
{
public:
	UGlobalVariable();
	~UGlobalVariable();

	UGlobalVariable(const UGlobalVariable& _Other) = delete;
	UGlobalVariable(UGlobalVariable&& _Other) noexcept = delete;
	UGlobalVariable& operator=(const UGlobalVariable& _Other) = delete;
	UGlobalVariable& operator=(UGlobalVariable&& _Other) noexcept = delete;

protected:

private:

};

