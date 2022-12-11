#include "OriginalStatus.h"
#include "../Engine/Image.h"
//コンストラクタ
OriginalStatus::OriginalStatus(GameObject* parent)
	: GameObject(parent, "OriginalStatus"), hPict_(-1)
{
}

//初期化
void OriginalStatus::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\OriginalStatus.png");
	assert(hPict_ >= 0);
	transform_.position_.x = 1.5f;
}

//更新
void OriginalStatus::Update()
{
}

//描画
void OriginalStatus::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void OriginalStatus::Release()
{
}