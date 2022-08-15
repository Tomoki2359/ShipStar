#include "LobbyScene.h"
#include "Image/LobbyCourse.h"
#include "Image/LobbyCustom.h"
#include "Image/LobbyPlay.h"

//コンストラクタ
LobbyScene::LobbyScene(GameObject* parent)
	: GameObject(parent, "LobbyScene"),mouseMoob_(true),lobby_(-1)
{
}

//初期化
void LobbyScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<LobbyCourse>(this);
	Instantiate<LobbyCustom>(this);
	Instantiate<LobbyPlay>(this);
}

//更新
void LobbyScene::Update()
{
	if (Input::IsKeyDown(DIK_W))
	{
		mouseMoob_ = false;
		lobby_++;
		if (lobby_ >= MAX_LOBBY)
		{
			lobby_ = LOBBY_COURSE;
		}
	}
	if (Input::IsKeyDown(DIK_S))
	{
		mouseMoob_ = false;
		lobby_--;
		if (lobby_ < 0)
		{
			lobby_ = LOBBY_CUSTOM;
		}
	}

	//マウスが動いたかどうか
	mousePos_ = mouseNext_;
	mouseNext_ = Input::GetMousePosition();
	if (mousePos_.x != mouseNext_.x && mousePos_.y != mouseNext_.y)
	{
		mouseMoob_ = true;
	}

	if (FindObject("LobbyPlay") == nullptr)
	{
			SCENE_CHANGE(SCENE_ID_MATCHING);
	}
	

	if (FindObject("LobbyCustom") == nullptr)
	{
			SCENE_CHANGE(SCENE_ID_CUSTOM);
	}

	//キー操作
	if (mouseMoob_ == false)
	{
		if (lobby_ == LOBBY_COURSE && Input::IsKeyDown(DIK_Z))
		{
		}
		if (lobby_ == LOBBY_PLAY && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_MATCHING);
		}
		if (lobby_ == LOBBY_CUSTOM && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_CUSTOM);
		}
	}
}

//描画
void LobbyScene::Draw()
{
}

//開放
void LobbyScene::Release()
{
}