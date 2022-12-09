#include "TitleOption.h"

//�R���X�g���N�^
TitleOption::TitleOption(GameObject* parent)
	: Button(parent, "TitleOption")
{
}

void TitleOption::InitialPoint()
{
	transform_.position_.y = -0.5f;
}

void TitleOption::SetFile()
{
	fileName[0] = L"Assets\\TitleOption.png";
}
