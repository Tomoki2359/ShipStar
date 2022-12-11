#include "OptionScene.h"
#include "Image/ButtonArrangement.h"
#include "Image/OptionImage.h"
#include "Image/Background.h"

//コンストラクタ
OptionScene::OptionScene(GameObject* parent)
	: GameObject(parent, "OptionScene")
{
}

//初期化
void OptionScene::Initialize()
{
	Instantiate<Background>(this);
	Instantiate<ButtonArrangement>(this);
	Instantiate<OptionImage>(this);
	SetScreen(0, 0, 0);
}

//更新
void OptionScene::Update()
{
}

//描画
void OptionScene::Draw()
{
}

//開放
void OptionScene::Release()
{
}