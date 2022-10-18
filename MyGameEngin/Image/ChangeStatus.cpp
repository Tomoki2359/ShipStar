#include "ChangeStatus.h"
#include "../Engine/Image.h"
//コンストラクタ
ChangeStatus::ChangeStatus(GameObject* parent)
	: GameObject(parent, "ChangeStatus"), hPict_(-1)
{
}

//初期化
void ChangeStatus::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\ChangeStatus.png");
	assert(hPict_ >= 0);
	transform_.position_.x = 0.5f;
}

//更新
void ChangeStatus::Update()
{
}

//描画
void ChangeStatus::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void ChangeStatus::Release()
{
}