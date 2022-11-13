#include "CookpitParts.h"

CookpitParts::CookpitParts(GameObject* parent)
	:Parts(parent, "CookpitParts")
{
	catagoryNum_ = PARTS_COCKPIT;
	SetParts(Option::GetParts(PARTS_COCKPIT));
	SetColor(Option::GetColor(PARTS_COCKPIT));
}

//void CookpitParts::SetPartsNum(int partsNum)
//{
//	partsNum_ = partsNum;
//}

int CookpitParts::GetPartsNum()
{
	return partsNum_;
}