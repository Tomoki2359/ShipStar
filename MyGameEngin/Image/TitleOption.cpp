#include "TitleOption.h"

//コンストラクタ
TitleOption::TitleOption(GameObject* parent)
	: Button(parent, "TitleOption")
{
}

void TitleOption::InitialPoint()
{
	transform_.position_.y = -0.5f;
}

//bool TitleOption::IsImage()
//{
//	if (MousePos_.x >= 570 && MousePos_.x <= 1050 && MousePos_.y > 600 && MousePos_.y <= 735)
//	{
//		return true;
//	}
//	return false;
//}

LPCWSTR TitleOption::SetFile()
{
	return L"Assets\\TitleOption.png";
}
