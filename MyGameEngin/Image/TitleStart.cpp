#include "TitleStart.h"

//コンストラクタ
TitleStart::TitleStart(GameObject* parent)
	: Button(parent, "TitleStart")
{
}

void TitleStart::InitialPoint()
{
	transform_.position_.y = -0.25f;
}

//bool TitleStart::IsImage()
//{
//	if (MousePos_.x >= 570 && MousePos_.x <= 1050 && MousePos_.y >= 465 && MousePos_.y <= 600)
//	{
//		return true;
//	}
//	return false;
//}

LPCWSTR TitleStart::SetFile()
{
	return L"Assets\\TitleStart.png";
}

