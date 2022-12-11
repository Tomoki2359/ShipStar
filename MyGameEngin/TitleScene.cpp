#include "TitleScene.h"
#include "Engine/Image.h"
#include "Image/TitleName.h"
#include "Image/Background.h"
#include "Image/TitleImage.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), alpha(0), start_(true)
{
}

//初期化
void TitleScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<Background>(this);
	Instantiate<TitleName>(this);
	Instantiate<TitleImage>(this);
	Image::AllSetAlpha(0);
}

//更新
void TitleScene::Update()
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
void TitleScene::Draw()
{
}

//開放
void TitleScene::Release()
{
}