#include "MatchingBackground.h"
#include "../Engine/Image.h"
#include "../Player.h"

//コンストラクタ
MatchingBackground::MatchingBackground(GameObject* parent)
	: GameObject(parent, "MatchingBackground"), hPict_(-1)
{
}

//初期化
void MatchingBackground::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\MatchingBackground.png");
	assert(hPict_ >= 0);
}

//更新
void MatchingBackground::Update()
{
}

//描画
void MatchingBackground::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void MatchingBackground::Release()
{
}