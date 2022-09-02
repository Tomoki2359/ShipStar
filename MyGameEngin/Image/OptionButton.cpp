#include "OptionButton.h"
#include "../Engine/Image.h"
//コンストラクタ
OptionButton::OptionButton(GameObject* parent)
	: GameObject(parent, "OptionButton"), hPict_(-1)
{
}

//初期化
void OptionButton::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\OptionButton.png");
	assert(hPict_ >= 0);
	transform_.position_.y = 0.125f;
}

//更新
void OptionButton::Update()
{
	//マウスの位置の取得
	XMFLOAT3 MousePos_;
	MousePos_ = Input::GetMousePosition();

	//画像の位置
	if (MousePos_.x >= 570 && MousePos_.x <= 1050 && MousePos_.y >= 280 && MousePos_.y <= 415)
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
void OptionButton::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void OptionButton::Release()
{
}