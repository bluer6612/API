#pragma once

static const int CropsCount = 44;
static const int CropsCountY = 4;

static int CropsNeedMoney[CropsCount] = { 0, 1, 2, 2, 3, 3, 5, 5, 7, 7, 9, 9, 9, 12, 12, 12, 14, 19, 16, 16, 16, 18, 18, 18, 24, 24, 27, 28, 32, 28, 35, 35, 35, 55, 50, 45, 60, 70, 60, 75, 75, 75 };
static int CropsNeedGrowTime[CropsCount] = { 70, 120, 150, 180, 200, 220, 230, 250, 270, 290, 310, 324, 340, 360, 380, 340, 420, 414, 438, 444, 492, 480, 500, 546, 504, 560, 520, 606, 550, 648, 624, 700, 660, 553, 654, 720, 680, 640, 780, 688, 798, 780 };
static int CropsNeedWater[CropsCount] = { 2, 3, 2, 3, 6, 5, 5, 4, 3, 7, 5, 4, 7, 8, 4, 8, 6, 5, 8, 7, 6, 8, 6, 8, 7, 5, 6, 7, 8, 7, 8, 6, 9, 8, 7, 9, 10, 9, 8, 10, 9, 10 };
static int CropsNeedRegrow[CropsCount] = { 1, 2, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 17, 18 };
static int CropsSellMoney[CropsCount] = { 3, 2, 3, 4, 4, 5, 4, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 15, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 24 };
static int CropsSellBio[CropsCount] = { 0, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 18 };

// Ό³Έν :
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

