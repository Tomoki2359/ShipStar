#include "CookpitParts.h"

CookpitParts::CookpitParts(GameObject* parent)
	:Parts(parent, "CookpitParts")
{
	catagoryNum_ = PARTS_COCKPIT;
	partsNum_ = Option::GetParts(PARTS_COCKPIT);
	SetParts(partsNum_);
	SetColor(Option::GetColor(PARTS_COCKPIT));
	Load();
	Union((PARTS_NAME)Option::GetParts(PARTS_BODY), partsNum_);
}

//void CookpitParts::SetPartsNum(int partsNum)
//{
//	partsNum_ = partsNum;
//}

int CookpitParts::GetPartsNum()
{
	return partsNum_;
}

void CookpitParts::GingaUnion(int partsNum)
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
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.125f;
		transform_.position_.z = 0.5f;
		break;
	case PARTS_SINDEN:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0.02f;
		transform_.position_.y = 0.15f;
		transform_.position_.z = 0;
		break;
	case PARTS_ZERO:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.05f;
		transform_.position_.z = 0.2f;
		break;
	default:
		break;
	}
}

void CookpitParts::MastangUnion(int partsNum)
{
	switch ((PARTS_NAME)partsNum)
	{
	case PARTS_GINGA:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.125f;
		transform_.position_.z = 0;
		break;
	case PARTS_MASTANG:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.15f;
		transform_.position_.z = 0.5f;
		break;
	case PARTS_SINDEN:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0.02f;
		transform_.position_.y = 0.2f;
		transform_.position_.z = 0;
		break;
	case PARTS_ZERO:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.2f;
		transform_.position_.z = -0.1f;
		break;
	default:
		break;
	}
}

void CookpitParts::SindenUnion(int partsNum)
{
	switch ((PARTS_NAME)partsNum)
	{
	case PARTS_GINGA:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.2f;
		transform_.position_.z = 0;
		break;
	case PARTS_MASTANG:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.25f;
		transform_.position_.z = 0.5f;
		break;
	case PARTS_SINDEN:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0.02f;
		transform_.position_.y = 0.25f;
		transform_.position_.z = -0.25f;
		break;
	case PARTS_ZERO:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.25f;
		transform_.position_.z = 0;
		break;
	default:
		break;
	}
}

void CookpitParts::ZeroUnion(int partsNum)
{
	switch ((PARTS_NAME)partsNum)
	{
	case PARTS_GINGA:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.2f;
		transform_.position_.z = -0.1f;
		break;
	case PARTS_MASTANG:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.2f;
		transform_.position_.z = 0.5f;
		break;
	case PARTS_SINDEN:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0.02f;
		transform_.position_.y = 0.2f;
		transform_.position_.z = -0.1f;
		break;
	case PARTS_ZERO:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.2f;
		transform_.position_.z = 0;
		break;
	default:
		break;
	}
}
