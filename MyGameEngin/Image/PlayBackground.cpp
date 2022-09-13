#include "PlayBackground.h"
#include "../Engine/Image.h"
//コンストラクタ
PlayBackground::PlayBackground(GameObject* parent)
	: GameObject(parent, "PlayBackground")
{
	hPict_[0] = -1;
	hPict_[1] = -1;
}

//初期化
void PlayBackground::Initialize()
{
	//モデルデータのロード
	hPict_[0] = Image::Load(L"Assets\\PlayBackground1.jpg");
	assert(hPict_[0] >= 0);

	hPict_[1] = Image::Load(L"Assets\\PlayBackground1.jpg");
	assert(hPict_[1] >= 0);
}

//更新
void PlayBackground::Update()
{
}

//描画
void PlayBackground::Draw()
{
	Transform trans = transform_;
	Image::SetTransform(hPict_[0], trans);
	Image::Draw(hPict_[0]);

	trans.position_.x += 2;
	Image::SetTransform(hPict_[1], trans);
	Image::Draw(hPict_[1]);
}

//開放
void PlayBackground::Release()
{
}