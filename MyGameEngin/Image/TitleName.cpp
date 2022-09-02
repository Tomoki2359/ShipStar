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
	hPict_ = Image::Load(L"Assets\\Title.png");
	assert(hPict_ >= 0);
	transform_.position_.y = 0.5f;
}

//更新
void TitleName::Update()
{
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