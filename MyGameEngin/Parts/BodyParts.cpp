#include "BodyParts.h"

BodyParts::BodyParts(GameObject* parent)
	:Parts(parent, "BodyParts")
{
	catagoryNum_ = PARTS_BODY;
	partsNum_ = Option::GetParts(PARTS_BODY);
	SetParts(partsNum_);
	SetColor(Option::GetColor(PARTS_BODY));
	Load();
	Union((PARTS_NAME)Option::GetParts(PARTS_BODY), partsNum_);
}

//void BodyParts::SetPartsNum(int partsNum)
//{
//	partsNum_ = partsNum;
//}

int BodyParts::GetPartsNum()
{
	return partsNum_;
}

void BodyParts::GingaUnion(int partsNum)
{
	transform_.scale_.x = 0.5f;
	transform_.scale_.y = 0.5f;
	transform_.scale_.z = 0.5f;
	transform_.position_.x = 0;
	transform_.position_.y = 0;
	transform_.position_.z = 0;
}

void BodyParts::MastangUnion(int partsNum)
{
	transform_.scale_.x = 0.5f;
	transform_.scale_.y = 0.5f;
	transform_.scale_.z = 0.5f;
	transform_.position_.x = 0;
	transform_.position_.y = 0.125f;
	transform_.position_.z = 0;
}

void BodyParts::SindenUnion(int partsNum)
{
	transform_.scale_.x = 0.5f;
	transform_.scale_.y = 0.5f;
	transform_.scale_.z = 0.5f;
	transform_.position_.x = 0;
	transform_.position_.y = 0.25f;
	transform_.position_.z = -0.25f;
}

void BodyParts::ZeroUnion(int partsNum)
{
	transform_.scale_.x = 0.5f;
	transform_.scale_.y = 0.5f;
	transform_.scale_.z = 0.5f;
	transform_.position_.x = 0;
	transform_.position_.y = 0.2f;
	transform_.position_.z = -0.1f;
}
