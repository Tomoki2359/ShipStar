#include "TitleName.h"
#include "../Engine/Image.h"
//コンストラクタ
TitleName::TitleName(GameObject* parent)
	: GameObject(parent, "TitleName"), hPict_(-1)
{
}

//初期化
void TitleName::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\Button.png");
	assert(hPict_ >= 0);
	transform_.scale_.x = 0.25;
	transform_.scale_.y = 0.125;
	transform_.position_.y = -0.5;
}

//更新
void TitleName::Update()
{
	XMFLOAT3 MousePos_;
	MousePos_ = Input::GetMousePosition();

	if (MousePos_.x >= 570 && MousePos_.x <= 1050 && MousePos_.y > 600 && MousePos_.y <= 735)
	{
		transform_.scale_.x = 0.3;
		transform_.scale_.y = 0.2;
		if (Input::IsMouceDown(0))
			KillMe();
	}
	else
	{
		transform_.scale_.x = 0.25;
		transform_.scale_.y = 0.125;
	}
}

//描画
void TitleName::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void TitleName::Release()
{
}