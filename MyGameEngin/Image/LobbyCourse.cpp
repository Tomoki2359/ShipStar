#include "LobbyCourse.h"
#include "../Engine/Image.h"
//コンストラクタ
LobbyCourse::LobbyCourse(GameObject* parent)
	: GameObject(parent, "LobbyCourse"), hPict_(-1)
{
}

//初期化
void LobbyCourse::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\LobbyCourse.png");
	assert(hPict_ >= 0);
	transform_.position_.x = -0.7f;
	transform_.position_.y = 0.7f;
}

//更新
void LobbyCourse::Update()
{
	//マウスの位置の取得
	XMFLOAT3 MousePos_;
	MousePos_ = Input::GetMousePosition();

	//画像の位置
	if (MousePos_.x >= 5 && MousePos_.x <= 320 && MousePos_.y >= 5 && MousePos_.y <= 150)
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
void LobbyCourse::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void LobbyCourse::Release()
{
}