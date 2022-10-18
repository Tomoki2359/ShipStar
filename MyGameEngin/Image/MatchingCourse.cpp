#include "MatchingCourse.h"
#include "../Engine/Image.h"
//コンストラクタ
MatchingCourse::MatchingCourse(GameObject* parent)
	: GameObject(parent, "MatchingCourse"), hPict_(-1)
{
}

//初期化
void MatchingCourse::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\MatchingCourse.png");
	assert(hPict_ >= 0);
	transform_.position_.y = 0.5f;
}

//更新
void MatchingCourse::Update()
{
}

//描画
void MatchingCourse::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void MatchingCourse::Release()
{
}