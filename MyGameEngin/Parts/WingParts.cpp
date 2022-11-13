#include "WingParts.h"

WingParts::WingParts(GameObject* parent)
	:Parts(parent, "WingParts")
{
	catagoryNum_ = PARTS_WING;
	SetParts(Option::GetParts(PARTS_WING));
	SetColor(Option::GetColor(PARTS_WING));
}

//void WingParts::SetPartsNum(int partsNum)
//{
//	partsNum_ = partsNum;
//}

int WingParts::GetPartsNum()
{
	return partsNum_;
}