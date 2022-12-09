#include "RetryButton.h"

//�R���X�g���N�^
RetryButton::RetryButton(GameObject* parent)
	: Button(parent, "RetryButton")
{
}

void RetryButton::InitialPoint()
{
	transform_.position_.x = 0.8f;
	transform_.position_.y = -0.8f;
}

void RetryButton::SetFile()
{
	fileName[0] = L"Assets\\retry.png";
}