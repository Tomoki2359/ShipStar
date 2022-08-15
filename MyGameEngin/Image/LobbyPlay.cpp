#include "LobbyPlay.h"
#include "../Engine/Image.h"
//コンストラクタ
LobbyPlay::LobbyPlay(GameObject * parent)
	: GameObject(parent, "LobbyPlay"), hPict_(-1)
{
}

//初期化
void LobbyPlay::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\Button.png");
	assert(hPict_ >= 0);
	transform_.scale_.x = 0.166;
	transform_.scale_.y = 0.166;
	transform_.position_.x = 0.8;
	transform_.position_.y = 0.8;
}

//更新
void LobbyPlay::Update()
{
	XMFLOAT3 MousePos_;
	MousePos_ = Input::GetMousePosition();

	if (MousePos_.x >= 1250 && MousePos_.x <= 1520 && MousePos_.y >= 5 && MousePos_.y <= 150)
	{
		transform_.scale_.x = 0.25;
		transform_.scale_.y = 0.25;
		if (Input::IsMouceDown(0))
			KillMe();
	}
	else
	{
		transform_.scale_.x = 0.166;
		transform_.scale_.y = 0.166;
	}
}

//描画
void LobbyPlay::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void LobbyPlay::Release()
{
}