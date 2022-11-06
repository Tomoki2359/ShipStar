#include "BodyParts.h"

BodyParts::BodyParts(GameObject* parent)
	:Parts(parent, "BodyParts")
{
	catagoryNum_ = PARTS_BODY;
	SetParts(Option::GetParts(PARTS_BODY));
}

//void BodyParts::SetPartsNum(int partsNum)
//{
//	partsNum_ = partsNum;
//}

int BodyParts::GetPartsNum()
{
	return partsNum_;
}