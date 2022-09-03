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

bool LobbyCustom::IsImage()
{
	if (MousePos_.x >= 1250 && MousePos_.x <= 1520 && MousePos_.y >= 650 && MousePos_.y <= 1080)
	{
		return true;
	}
	return false;
}

LPCWSTR LobbyCustom::SetFile()
{
	return L"Assets\\LobbyCustom.png";
}