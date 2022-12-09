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

void TitleStart::SetFile()
{
	fileName[0] = L"Assets\\TitleStart.png";
}