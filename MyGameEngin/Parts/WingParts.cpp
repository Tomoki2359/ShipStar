#include "WingParts.h"

WingParts::WingParts(GameObject* parent)
	:Parts(parent, "WingParts")
{
	catagoryNum_ = PARTS_WING;
	partsNum_ = Option::GetParts(PARTS_WING);
	SetParts(partsNum_);
	SetColor(Option::GetColor(PARTS_WING));
	Load();
	Union((PARTS_NAME)Option::GetParts(PARTS_BODY), partsNum_);
}

//void WingParts::SetPartsNum(int partsNum)
//{
//	partsNum_ = partsNum;
//}

int WingParts::GetPartsNum()
{
	return partsNum_;
}

void WingParts::GingaUnion(int partsNum)
{
	switch ((PARTS_NAME)partsNum)
	{
	case PARTS_GINGA:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0;
		transform_.position_.z = 0;
		break;
	case PARTS_MASTANG:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.25f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.45f;
		transform_.position_.z = 0.3f;
		break;
	case PARTS_SINDEN:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0.02f;
		transform_.position_.y = 0.42f;
		transform_.position_.z = -0.4;
		break;
	case PARTS_ZERO:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.4f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.35f;
		transform_.position_.z = 0.2f;
		break;
	default:
		break;
	}
}

void WingParts::MastangUnion(int partsNum)
{
	switch ((PARTS_NAME)partsNum)
	{
	case PARTS_GINGA:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = -0.1f;
		transform_.position_.z = 0;
		break;
	case PARTS_MASTANG:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.25f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.35f;
		transform_.position_.z = 0.3f;
		break;
	case PARTS_SINDEN:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0.02f;
		transform_.position_.y = 0.32f;
		transform_.position_.z = -0.4f;
		break;
	case PARTS_ZERO:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.4f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.25f;
		transform_.position_.z = 0.2f;
		break;
	default:
		break;
	}
}

void WingParts::SindenUnion(int partsNum)
{
	switch ((PARTS_NAME)partsNum)
	{
	case PARTS_GINGA:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = -0.1f;
		transform_.position_.z = 0.1f;
		break;
	case PARTS_MASTANG:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.25f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.35f;
		transform_.position_.z = 0.3f;
		break;
	case PARTS_SINDEN:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0.02f;
		transform_.position_.y = 0.32f;
		transform_.position_.z = 0;
		break;
	case PARTS_ZERO:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.4f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.25f;
		transform_.position_.z = 0.2f;
		break;
	default:
		break;
	}
}

void WingParts::ZeroUnion(int partsNum)
{
	switch ((PARTS_NAME)partsNum)
	{
	case PARTS_GINGA:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0;
		transform_.position_.z = 0;
		break;
	case PARTS_MASTANG:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.25f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.35f;
		transform_.position_.z = 0.3f;
		break;
	case PARTS_SINDEN:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0.02;
		transform_.position_.y = 0.35f;
		transform_.position_.z = -0.2f;
		break;
	case PARTS_ZERO:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.4f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.25f;
		transform_.position_.z = 0.2f;
		break;
	default:
		break;
	}
}
