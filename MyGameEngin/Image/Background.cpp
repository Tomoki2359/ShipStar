#include "Background.h"
#include "../Engine/Image.h"
//コンストラクタ
Background::Background(GameObject* parent)
	: GameObject(parent, "Background"), hPict_(-1)
{
}

//初期化
void Background::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\Background.jpg");
	assert(hPict_ >= 0);
}

//更新
void Background::Update()
{
}

//描画
void Background::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void Background::Release()
{
}