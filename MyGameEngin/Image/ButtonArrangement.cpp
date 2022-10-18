#include "ButtonArrangement.h"
#include "../Engine/Image.h"
//コンストラクタ
ButtonArrangement::ButtonArrangement(GameObject* parent)
	: GameObject(parent, "ButtonArrangement"), hPict_(-1)
{
}

//初期化
void ButtonArrangement::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\ButtonArrangement.png");
	assert(hPict_ >= 0);
}

//更新
void ButtonArrangement::Update()
{
}

//描画
void ButtonArrangement::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void ButtonArrangement::Release()
{
}