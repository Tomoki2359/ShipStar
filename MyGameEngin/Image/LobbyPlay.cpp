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
	hPict_ = Image::Load(L"Assets\\LobbyPlay.png");
	assert(hPict_ >= 0);
	transform_.position_.x = 0.7f;
	transform_.position_.y = 0.7f;
}

//更新
void LobbyPlay::Update()
{
	//マウスの位置の取得
	XMFLOAT3 MousePos_;
	MousePos_ = Input::GetMousePosition();

	//画像の位置
	if (MousePos_.x >= 1250 && MousePos_.x <= 1520 && MousePos_.y >= 5 && MousePos_.y <= 150)
	{
		transform_.scale_.x = 1.1;
		transform_.scale_.y = 1.1;
		if (Input::IsMouceDown(0))
			KillMe();
	}
	else
	{
		transform_.scale_.x = 1.0f;
		transform_.scale_.y = 1.0f;
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