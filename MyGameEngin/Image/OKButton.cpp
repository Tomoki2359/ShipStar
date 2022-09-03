#include "OKButton.h"

//コンストラクタ
OKButton::OKButton(GameObject* parent)
	: Button(parent, "OKButton")
{
}

void OKButton::InitialPoint()
{
	transform_.position_.x = 0.8f;
	transform_.position_.y = -0.8f;
}

bool OKButton::IsImage()
{
	if (MousePos_.x >= 1250 && MousePos_.x <= 1520 && MousePos_.y >= 650 && MousePos_.y <= 1080)
	{
		return true;
	}
	return false;
}

LPCWSTR OKButton::SetFile()
{
	return L"Assets\\OKButton.png";
}