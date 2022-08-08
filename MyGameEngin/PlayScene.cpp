#include "PlayScene.h"
#include "Course.h"
#include "Player.h"
#include "Computer.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<Player>(this);
	Instantiate<Computer>(this);
	Instantiate<Course>(this);
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}