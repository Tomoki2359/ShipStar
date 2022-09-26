#include "MatchingStart.h"

//コンストラクタ
MatchingStart::MatchingStart(GameObject* parent)
	: Button(parent, "MatchingStart")
{
}

void MatchingStart::InitialPoint()
{
	transform_.position_.y = -0.25f;
}

//bool MatchingStart::IsImage()
//{
//	if (MousePos_.x >= 320 && MousePos_.x <= 1250 && MousePos_.y >= 465 && MousePos_.y <= 600)
//	{
//		return true;
//	}
//	return false;
//}

LPCWSTR MatchingStart::SetFile()
{
	return L"Assets\\MatchingStart.png";
}