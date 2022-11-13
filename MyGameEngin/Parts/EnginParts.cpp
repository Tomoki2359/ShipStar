#include "EnginParts.h"

EnginParts::EnginParts(GameObject* parent)
	:Parts(parent, "EnginParts")
{
	catagoryNum_ = PARTS_ENGINE;
	SetParts(Option::GetParts(PARTS_ENGINE));
	SetColor(Option::GetColor(PARTS_ENGINE));
}

//void EnginParts::SetPartsNum(int partsNum)
//{
//	partsNum_ = partsNum;
//}

int EnginParts::GetPartsNum()
{
	return partsNum_;
}
