#include "OptionButton.h"

//�R���X�g���N�^
OptionButton::OptionButton(GameObject* parent)
	: Button(parent, "OptionButton")
{
}

void OptionButton::InitialPoint()
{
	transform_.position_.y = 0.125f;
}

void OptionButton::SetFile()
{
	fileName[0] = L"Assets\\OptionButton.png";
}
