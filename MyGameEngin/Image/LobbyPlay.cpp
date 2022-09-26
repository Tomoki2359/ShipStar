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

//bool LobbyPlay::IsImage()
//{
//	if (MousePos_.x >= 1250 && MousePos_.x <= 1520 && MousePos_.y >= 5 && MousePos_.y <= 150)
//	{
//		return true;
//	}
//	return false;
//}

LPCWSTR LobbyPlay::SetFile()
{
	return L"Assets\\LobbyPlay.png";
}