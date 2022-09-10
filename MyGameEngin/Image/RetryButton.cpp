#include "RetryButton.h"

//コンストラクタ
RetryButton::RetryButton(GameObject* parent)
	: Button(parent, "RetryButton")
{
}

void RetryButton::InitialPoint()
{
	transform_.position_.x = 0.8f;
	transform_.position_.y = -0.8f;
}

bool RetryButton::IsImage()
{
	if (MousePos_.x >= 1250 && MousePos_.x <= 1520 && MousePos_.y >= 650 && MousePos_.y <= 1080)
	{
		return true;
	}
	return false;
}

LPCWSTR RetryButton::SetFile()
{
	return L"Assets\\retry.png";
}