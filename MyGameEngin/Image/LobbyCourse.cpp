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
	hPict_ = Image::Load(L"Assets\\Button.png");
	assert(hPict_ >= 0);
	transform_.scale_.x = 0.166f;
	transform_.scale_.y = 0.166f;
	transform_.position_.x = -0.8f;
	transform_.position_.y = 0.8f;
}

//更新
void LobbyCourse::Update()
{
	XMFLOAT3 MousePos_;
	MousePos_ = Input::GetMousePosition();

	if (MousePos_.x >= 5 && MousePos_.x <= 320 && MousePos_.y >= 5 && MousePos_.y <= 150)
	{
		transform_.scale_.x = 0.25f;
		transform_.scale_.y = 0.25f;
		if (Input::IsMouceDown(0))
			KillMe();
	}
	else
	{
		transform_.scale_.x = 0.166f;
		transform_.scale_.y = 0.166f;
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