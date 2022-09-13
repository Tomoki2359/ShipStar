#include "PlayBackground.h"
#include "../Engine/Image.h"
//コンストラクタ
PlayBackground::PlayBackground(GameObject* parent)
	: GameObject(parent, "PlayBackground")
{
	hPict[0] =
}

//初期化
void PlayBackground::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\PlayBackground.jpg");
	assert(hPict_ >= 0);
}

//更新
void PlayBackground::Update()
{
}

//描画
void PlayBackground::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void PlayBackground::Release()
{
}