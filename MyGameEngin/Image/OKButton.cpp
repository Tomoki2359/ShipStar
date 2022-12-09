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

void OKButton::SetFile()
{
	fileName[0] = L"Assets\\OKButton.png";
}