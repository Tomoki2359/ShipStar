#include "MatchingScene.h"
#include "Image/MatchingCourse.h"
#include "Image/MatchingBackground.h"
#include "Image/MatchingImage.h"
#include "Engine/Image.h"

//コンストラクタ
MatchingScene::MatchingScene(GameObject* parent)
	: GameObject(parent, "MatchingScene"), alpha(0), start_(true)
{
}

//初期化
void MatchingScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<MatchingBackground>(this);
	Instantiate<MatchingCourse>(this);
	Instantiate<MatchingImage>(this);
	Image::AllSetAlpha(0);
}

//更新
void MatchingScene::Update()
{
	if (start_)
	{
		if (alpha == UINT8_MAX)
		{
			start_ = false;
		}
		Image::AllSetAlpha(alpha);
		alpha += 2;
	}
}

//描画
void MatchingScene::Draw()
{
}

//開放
void MatchingScene::Release()
{
}