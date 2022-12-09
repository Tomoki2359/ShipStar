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

void BackButton::SetFile()
{
	fileName[0] = L"Assets\\BackButton.png";
}