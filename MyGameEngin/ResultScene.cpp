#include "ResultScene.h"

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene")
{
}

//初期化
void ResultScene::Initialize()
{
	SetScreen(0, 0, 0);
}

//更新
void ResultScene::Update()
{
	SCENE_CHANGE(SCENE_ID_LOBBY);
}

//描画
void ResultScene::Draw()
{
}

//開放
void ResultScene::Release()
{
}