#include "BackButton.h"
#include "../Engine/Image.h"
//コンストラクタ
BackButton::BackButton(GameObject* parent)
	: GameObject(parent, "BackButton"), hPict_(-1)
{
}

//初期化
void BackButton::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\BackButton.png");
	assert(hPict_ >= 0);
	transform_.position_.x = -0.8f;
	transform_.position_.y = -0.8f;
}

//更新
void BackButton::Update()
{
	//マウスの位置の取得
	XMFLOAT3 MousePos_;
	MousePos_ = Input::GetMousePosition();

	//画像の位置
	if (MousePos_.x >= 5 && MousePos_.x <= 320 && MousePos_.y >= 650 && MousePos_.y <= 1080)
	{
		transform_.scale_.x = 1.1f;
		transform_.scale_.y = 1.1f;
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
void BackButton::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void BackButton::Release()
{
}