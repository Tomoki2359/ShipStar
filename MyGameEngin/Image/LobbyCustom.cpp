#include "LobbyCustom.h"

//コンストラクタ
LobbyCustom::LobbyCustom(GameObject* parent)
	: Button(parent, "LobbyCustom")
{
}

void LobbyCustom::InitialPoint()
{
	transform_.position_.x = 0.7f;
	transform_.position_.y = -0.7f;
}

void LobbyCustom::SetFile()
{
	fileName[0] = L"Assets\\LobbyCustom.png";
}