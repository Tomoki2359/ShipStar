#include "ModeSelection.h"
#include "../Engine/Image.h"
#include "../Option.h"

//コンストラクタ
ModeSelection::ModeSelection(GameObject* parent)
	: Button(parent, "ModeSelection")
{
	SIZE = MODE_ONLYGHOST + 1;
}

void ModeSelection::InitialPoint()
{
	for (int i = 0; i < SIZE; i++)
	{
		trans_[i].position_ = XMFLOAT3{ 0,  0.8f - i * 0.4f ,0 };
		trans_[i].scale_.x = 0.0f;
		trans_[i].scale_.y = 0.0f;
	}
}

void ModeSelection::SetFile()
{
	fileName[0] = L"Assets\\Mode1.png";
	fileName[1] = L"Assets\\Mode2.png";
	fileName[2] = L"Assets\\Mode3.png";
	fileName[3] = L"Assets\\Mode4.png";
	fileName[4] = L"Assets\\Mode5.png";
}

void ModeSelection::PutButton()
{
	if (trans_[0].scale_.x <= 0)
	{
		Option::SetMode(tucheNumber_);
		KillMe();
	}
	for (int i = 0; i < SIZE; i++)
	{
		trans_[i].scale_.x -= 0.1f;
		trans_[i].scale_.y -= 0.1f;
	}
}

bool ModeSelection::IsAddCondition()
{
	if (trans_[0].scale_.x >= 1.0f)
	{
		return true;
	}
	return false;
}

void ModeSelection::TucheButton(int number)
{
	trans_[number].scale_.x = 1.1f;
	trans_[number].scale_.y = 1.1f;
}

void ModeSelection::NoTucheButton(int number)
{
	trans_[number].scale_.x += 0.1f;
	trans_[number].scale_.y += 0.1f;
	if (trans_[number].scale_.x >= 1.0f)
	{
		trans_[number].scale_.x = 1.0f;
		trans_[number].scale_.y = 1.0f;
	}
}
