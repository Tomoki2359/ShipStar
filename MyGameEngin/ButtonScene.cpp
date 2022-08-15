#include "ButtonScene.h"
#include "Image/BackButton.h"
#include "Image/OKButton.h"

//コンストラクタ
ButtonScene::ButtonScene(GameObject* parent)
	: GameObject(parent, "ButtonScene"), mouseMoob_(false), button_(-1)
{
}

//初期化
void ButtonScene::Initialize()
{
	Instantiate<BackButton>(this);
	Instantiate<OKButton>(this);
	SetScreen(0, 0, 0);
}

//更新
void ButtonScene::Update()
{
	if (Input::IsKeyDown(DIK_W))
	{
		mouseMoob_ = false;
		button_++;
		if (button_ >= MAX_BUTTON)
		{
			button_ = BUTTON_BACK;
		}
	}
	if (Input::IsKeyDown(DIK_S))
	{
		mouseMoob_ = false;
		button_--;
		if (button_ < 0)
		{
			button_ = BUTTON_OK;
		}
	}

	//マウスが動いたかどうか
	mousePos_ = mouseNext_;
	mouseNext_ = Input::GetMousePosition();
	if (mousePos_.x != mouseNext_.x && mousePos_.y != mouseNext_.y)
	{
		mouseMoob_ = true;
	}

	if (FindObject("BackButton") == nullptr)
	{
		SCENE_CHANGE(SCENE_ID_OPTION);
	}
	if (FindObject("OKButton") == nullptr)
	{
		SCENE_CHANGE(SCENE_ID_OPTION);
	}

	//キー操作
	if (mouseMoob_ == false)
	{
		if (button_ == BUTTON_BACK && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_OPTION);
		}
		if (button_ == BUTTON_OK && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_OPTION);
		}
	}
}

//描画
void ButtonScene::Draw()
{
}

//開放
void ButtonScene::Release()
{
}