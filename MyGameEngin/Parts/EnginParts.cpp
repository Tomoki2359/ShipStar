#include "EnginParts.h"

EnginParts::EnginParts(GameObject* parent)
	:Parts(parent, "EnginParts")
{
	catagoryNum_ = PARTS_ENGINE;
	partsNum_ = Option::GetParts(PARTS_ENGINE);
	SetParts(partsNum_);
	SetColor(Option::GetColor(PARTS_ENGINE));
	Load();
	Union((PARTS_NAME)Option::GetParts(PARTS_BODY), partsNum_);
}

//void EnginParts::SetPartsNum(int partsNum)
//{
//	partsNum_ = partsNum;
//}

int EnginParts::GetPartsNum()
{
	return partsNum_;
}

void EnginParts::GingaUnion(int partsNum)
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
		transform_.position_.y = 0;
		transform_.position_.z = 0;
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
		transform_.scale_.x = 0.4;
		transform_.scale_.y = 0.4;
		transform_.scale_.z = 0.4;
		transform_.position_.x = 0;
		transform_.position_.y = 0.15f;
		transform_.position_.z = 0.6f;
		break;
	default:
		break;
	}
}

void EnginParts::MastangUnion(int partsNum)
{
	switch (partsNum)
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
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.125;
		transform_.position_.z = 0;
		break;
	case PARTS_SINDEN:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.275f;
		transform_.position_.z = -0.2f;
		break;
	case PARTS_ZERO:
		transform_.scale_.x = 0.45;
		transform_.scale_.y = 0.45;
		transform_.scale_.z = 0.4f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.225f;
		transform_.position_.z = 0.4f;
		break;
	default:
		break;
	}
}

void EnginParts::SindenUnion(int partsNum)
{
	switch (partsNum)
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
		transform_.scale_.x = 1.0f;
		transform_.scale_.y = 1.0f;
		transform_.scale_.z = 1.0f;
		transform_.position_.x = 0;
		transform_.position_.y = -0.3f;
		transform_.position_.z = -2.1f;
		break;
	case PARTS_SINDEN:
		transform_.scale_.x = 0.5f;
		transform_.scale_.y = 0.5f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.25;
		transform_.position_.z = -0.25;
		break;
	case PARTS_ZERO:
		transform_.scale_.x = 0.55f;
		transform_.scale_.y = 0.55f;
		transform_.scale_.z = 0.5f;
		transform_.position_.x = 0;
		transform_.position_.y = 0.2f;
		transform_.position_.z = 0.25f;
		break;
	default:
		break;
	}
}

void EnginParts::ZeroUnion(int partsNum)
{
	switch (partsNum)
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
		transform_.scale_.x = 1.1f;
		transform_.scale_.y = 1.1f;
		transform_.scale_.z = 1.0f;
		transform_.position_.x = 0;
		transform_.position_.y = -0.38f;
		transform_.position_.z = -2.35f;
		break;
	case PARTS_SINDEN:
		transform_.scale_.x = 1.0f;
		transform_.scale_.y = 1.0f;
		transform_.scale_.z = 1.0f;
		transform_.position_.x = 0;
		transform_.position_.y = -0.05f;
		transform_.position_.z = -2.6f;
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
