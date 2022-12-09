#include "FixeButton.h"

//�R���X�g���N�^
FixeButton::FixeButton(GameObject* parent)
	: Button(parent, "FixeButton")
{
}

void FixeButton::InitialPoint()
{
	transform_.position_.x = 0.8f;
	transform_.position_.y = -0.8f;
}

void FixeButton::SetFile()
{
	fileName[0] = L"Assets\\FixeButton.png";
}