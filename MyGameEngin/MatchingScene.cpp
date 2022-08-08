#include "MatchingScene.h"

//コンストラクタ
MatchingScene::MatchingScene(GameObject* parent)
	: GameObject(parent, "MatchingScene")
{
}

//初期化
void MatchingScene::Initialize()
{
	SetScreen(0, 0, 0);
}

//更新
void MatchingScene::Update()
{
	//SCENE_CHANGE(SCENE_ID_LOBBY);
	//SCENE_CHANGE(SCENE_ID_PLAY);
}

//描画
void MatchingScene::Draw()
{
}

//開放
void MatchingScene::Release()
{
}