#include "CouseMap.h"
#include "../Engine/Image.h"
//コンストラクタ
CouseMap::CouseMap(GameObject* parent)
	: GameObject(parent, "CouseMap"), hPict_(-1)
{
}

//初期化
void CouseMap::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\CouseMap1.png");
	assert(hPict_ >= 0);
	transform_.scale_.x = 0.125f;
	transform_.scale_.y = 0.125f;
	transform_.position_.x = 0.8;
	transform_.position_.y = 0.7;
}

//更新
void CouseMap::Update()
{
}

//描画
void CouseMap::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void CouseMap::Release()
{
}