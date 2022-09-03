#include "OptionButton.h"

//コンストラクタ
OptionButton::OptionButton(GameObject* parent)
	: Button(parent, "OptionButton")
{
}

void OptionButton::InitialPoint()
{
	transform_.position_.y = 0.125f;
}

bool OptionButton::IsImage()
{
	if (MousePos_.x >= 570 && MousePos_.x <= 1050 && MousePos_.y >= 280 && MousePos_.y <= 415)
	{
		return true;
	}
	return false;
}

LPCWSTR OptionButton::SetFile()
{
	return L"Assets\\OptionButton.png";
}
