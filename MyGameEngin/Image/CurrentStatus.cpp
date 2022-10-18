#include "CurrentStatus.h"
#include "../Engine/Image.h"
//コンストラクタ
CurrentStatus::CurrentStatus(GameObject* parent)
	: GameObject(parent, "CurrentStatus"), hPict_(-1)
{
}

//初期化
void CurrentStatus::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\CurrentStatus.png");
	assert(hPict_ >= 0);
	transform_.position_.x = -0.5f;
}

//更新
void CurrentStatus::Update()
{
}

//描画
void CurrentStatus::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void CurrentStatus::Release()
{
}