#include "MatchingStart.h"
#include "../Engine/Image.h"
//コンストラクタ
MatchingStart::MatchingStart(GameObject* parent)
	: GameObject(parent, "MatchingStart"), hPict_(-1)
{
}

//初期化
void MatchingStart::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\Button.png");
	assert(hPict_ >= 0);
	transform_.scale_.x = 0.5;
	transform_.scale_.y = 0.166;
	transform_.position_.y = -0.25;
}

//更新
void MatchingStart::Update()
{
	XMFLOAT3 MousePos_;
	MousePos_ = Input::GetMousePosition();

	if (MousePos_.x >= 320 && MousePos_.x <= 1250 && MousePos_.y >= 465 && MousePos_.y <= 600)
	{
		transform_.scale_.x = 0.6;
		transform_.scale_.y = 0.25;
		if (Input::IsMouceDown(0))
			KillMe();
	}
	else
	{
		transform_.scale_.x = 0.5;
		transform_.scale_.y = 0.166;
	}
}

//描画
void MatchingStart::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void MatchingStart::Release()
{
}