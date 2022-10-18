#include "FixeButton.h"

//コンストラクタ
FixeButton::FixeButton(GameObject* parent)
	: Button(parent, "FixeButton")
{
}

void FixeButton::InitialPoint()
{
	transform_.position_.x = 0.8f;
	transform_.position_.y = -0.8f;
}

//bool FixeButton::IsImage()
//{
//	if (MousePos_.x >= 1250 && MousePos_.x <= 1520 && MousePos_.y >= 650 && MousePos_.y <= 1080)
//	{
//		return true;
//	}
//	return false;
//}

LPCWSTR FixeButton::SetFile()
{
	return L"Assets\\FixeButton.png";
}