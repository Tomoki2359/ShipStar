#include "CustomScene.h"

//コンストラクタ
CustomScene::CustomScene(GameObject* parent)
	: GameObject(parent, "CustomScene")
{
}

//初期化
void CustomScene::Initialize()
{
	SetScreen(0, 0, 0);
}

//更新
void CustomScene::Update()
{
	//SCENE_CHANGE(SCENE_ID_LOBBY);
}

//描画
void CustomScene::Draw()
{
}

//開放
void CustomScene::Release()
{
}