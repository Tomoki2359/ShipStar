#include "ResultScene.h"
#include "Image/BackButton.h"
#include "Image/OKButton.h"

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene"),mouseMoob_(true),result_(-1)
{
}

//初期化
void ResultScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<BackButton>(this);
	Instantiate<OKButton>(this);
}

//更新
void ResultScene::Update()
{
	if (Input::IsKeyDown(DIK_W))
	{
		result_++;
		mouseMoob_ = false;
		if (result_ >= MAX_RESULT)
		{
			result_ = RESULT_BACK;
		}
	}
	if (Input::IsKeyDown(DIK_S))
	{
		result_--;
		mouseMoob_ = false;
		if (result_ < 0)
		{
			result_ = RESULT_OK;
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
		SCENE_CHANGE(SCENE_ID_LOBBY);
	}

	if (FindObject("OKButton") == nullptr)
	{
		SCENE_CHANGE(SCENE_ID_PLAY);
	}

	//キー操作
	if (mouseMoob_ == false)
	{
		if (result_ == RESULT_BACK && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_LOBBY);
		}
		if (result_ == RESULT_OK && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_PLAY);
		}
	}
}

//描画
void ResultScene::Draw()
{
}

//開放
void ResultScene::Release()
{
}