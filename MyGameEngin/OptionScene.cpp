#include "OptionScene.h"
#include "Image/BackButton.h"

//コンストラクタ
OptionScene::OptionScene(GameObject* parent)
	: GameObject(parent, "OptionScene")
{
}

//初期化
void OptionScene::Initialize()
{
	Instantiate<BackButton>(this);
	SetScreen(0, 0, 0);
}

//更新
void OptionScene::Update()
{
	if (FindObject("BackButton") == nullptr)
	{
		SCENE_CHANGE(SCENE_ID_TITLE);
	}
}

//描画
void OptionScene::Draw()
{
}

//開放
void OptionScene::Release()
{
}