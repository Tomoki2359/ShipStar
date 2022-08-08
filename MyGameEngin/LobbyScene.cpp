#include "LobbyScene.h"

//コンストラクタ
LobbyScene::LobbyScene(GameObject* parent)
	: GameObject(parent, "LobbyScene")
{
}

//初期化
void LobbyScene::Initialize()
{
	SetScreen(0, 0, 0);
}

//更新
void LobbyScene::Update()
{
	SCENE_CHANGE(SCENE_ID_MATCHING);
	SCENE_CHANGE(SCENE_ID_CUSTOM);
}

//描画
void LobbyScene::Draw()
{
}

//開放
void LobbyScene::Release()
{
}