#include "PartsList.h"
#include "../Engine/Image.h"
//コンストラクタ
PartsList::PartsList(GameObject* parent)
	: GameObject(parent, "PartsList"), hPict_(-1)
{
}

//初期化
void PartsList::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\PartsList.png");
	assert(hPict_ >= 0);
	transform_.position_.x = 0.5f;
}

//更新
void PartsList::Update()
{
}

//描画
void PartsList::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void PartsList::Release()
{
}