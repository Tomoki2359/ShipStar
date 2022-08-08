#include "TitleScene.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
}

//初期化
void TitleScene::Initialize()
{
	SetScreen(0, 0, 0);
}

//更新
void TitleScene::Update()
{
	//SCENE_CHANGE(SCENE_ID_LOBBY);
	SCENE_CHANGE(SCENE_ID_PLAY);
}

//描画
void TitleScene::Draw()
{
}

//開放
void TitleScene::Release()
{
}