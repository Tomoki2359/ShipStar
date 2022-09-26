#include "BackButton.h"

//コンストラクタ
BackButton::BackButton(GameObject* parent)
	: Button(parent, "BackButton")
{
}

void BackButton::InitialPoint()
{
	transform_.position_.x = -0.8f;
	transform_.position_.y = -0.8f;
}

//bool BackButton::IsImage()
//{
//	if (MousePos_.x >= 5 && MousePos_.x <= 320 && MousePos_.y >= 650 && MousePos_.y <= 1080)
//	{
//		return true;
//	}
//	return false;
//}

LPCWSTR BackButton::SetFile()
{
	return L"Assets\\BackButton.png";
}