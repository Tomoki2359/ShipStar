#include "MatchingStart.h"

//�R���X�g���N�^
MatchingStart::MatchingStart(GameObject* parent)
	: Button(parent, "MatchingStart")
{
}

void MatchingStart::InitialPoint()
{
	transform_.position_.y = -0.25f;
}

void MatchingStart::SetFile()
{
	fileName[0] = L"Assets\\MatchingStart.png";
}