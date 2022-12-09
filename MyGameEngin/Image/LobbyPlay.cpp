#include "LobbyPlay.h"

//コンストラクタ
LobbyPlay::LobbyPlay(GameObject* parent)
	: Button(parent, "LobbyPlay")
{
}

void LobbyPlay::InitialPoint()
{
	transform_.position_.x = 0.7f;
	transform_.position_.y = 0.7f;
}

void LobbyPlay::SetFile()
{
	fileName[0] = L"Assets\\LobbyPlay.png";
}