#include "LobbyCourse.h"

//コンストラクタ
LobbyCourse::LobbyCourse(GameObject* parent)
	: Button(parent, "LobbyCourse")
{
}

void LobbyCourse::InitialPoint()
{
	transform_.position_.x = -0.7f;
	transform_.position_.y = 0.7f;
}

bool LobbyCourse::IsImage()
{
	if (MousePos_.x >= 5 && MousePos_.x <= 320 && MousePos_.y >= 5 && MousePos_.y <= 150)
	{
		return true;
	}
	return false;
}

LPCWSTR LobbyCourse::SetFile()
{
	return L"Assets\\LobbyCourse.png";
}