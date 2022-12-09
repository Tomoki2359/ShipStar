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

void LobbyCourse::SetFile()
{
	fileName[0] = L"Assets\\LobbyCourse.png";
}