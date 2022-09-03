#include "OptionVolume.h"

//コンストラクタ
OptionVolume::OptionVolume(GameObject* parent)
	: Button(parent, "OptionVolume")
{
}

void OptionVolume::InitialPoint()
{
	transform_.position_.y = -0.25f;
}

bool OptionVolume::IsImage()
{
	if (MousePos_.x >= 570 && MousePos_.x <= 1050 && MousePos_.y >= 465 && MousePos_.y <= 600)
	{
		return true;
	}
	return false;
}

LPCWSTR OptionVolume::SetFile()
{
	return L"Assets\\OptionVolume.png";
}
