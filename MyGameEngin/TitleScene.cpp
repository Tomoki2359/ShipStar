#include "TitleScene.h"
#include "Engine/Input.h"
#include "Image/TitleStart.h"
#include "Image/TitleOption.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),mouseMoob_(true),title_(-1)
{
}

//初期化
void TitleScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<TitleStart>(this);
	Instantiate<TitleOption>(this);
}

//更新
void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_W))
	{
		mouseMoob_ = false;
		title_++;
		if (title_ >= MAX_TITLE)
		{
			title_ = TITLE_START;
		}
	}
	if (Input::IsKeyDown(DIK_S))
	{
		mouseMoob_ = false;
		title_--;
		if (title_ < 0)
		{
			title_ = TITLE_OPTION;
		}
	}

	//マウスが動いたかどうか
	mousePos_ = mouseNext_;
	mouseNext_ = Input::GetMousePosition();
	if (mousePos_.x != mouseNext_.x && mousePos_.y != mouseNext_.y)
	{
		mouseMoob_ = true;
	}

	if (FindObject("TitleStart") == nullptr)
	{ 
			SCENE_CHANGE(SCENE_ID_LOBBY);
	}

	if (FindObject("TitleOption") == nullptr)
	{
			SCENE_CHANGE(SCENE_ID_OPTION);
	}

	//キー操作
	if (mouseMoob_ == false)
	{
		if (title_ == TITLE_START && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_LOBBY);
		}
		if (title_ == TITLE_OPTION && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_OPTION);
		}
	}
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