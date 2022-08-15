#include "OptionScene.h"
#include "Image/BackButton.h"
#include "Image/OptionButton.h"
#include "Image/OptionVolume.h"

//コンストラクタ
OptionScene::OptionScene(GameObject* parent)
	: GameObject(parent, "OptionScene")
{
}

//初期化
void OptionScene::Initialize()
{
	Instantiate<BackButton>(this);
	Instantiate<OptionButton>(this);
	Instantiate<OptionVolume>(this);
	SetScreen(0, 0, 0);
}

//更新
void OptionScene::Update()
{
	if (Input::IsKeyDown(DIK_W))
	{
		mouseMoob_ = false;
		option_++;
		if (option_ >= MAX_OPTION)
		{
			option_ = OPTION_BACK;
		}
	}
	if (Input::IsKeyDown(DIK_S))
	{
		mouseMoob_ = false;
		option_--;
		if (option_ < 0)
		{
			option_ = OPTION_VOLUME;
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
		SCENE_CHANGE(SCENE_ID_TITLE);
	}

	if (FindObject("OptionButton") == nullptr)
	{
		SCENE_CHANGE(SCENE_ID_BUTTON);
	}

	if (FindObject("OptionVolume") == nullptr)
	{
		SCENE_CHANGE(SCENE_ID_VOLUME);
	}

	//キー操作
	if (mouseMoob_ == false)
	{
		if (option_ == OPTION_BACK && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_TITLE);
		}
		if (option_ == OPTION_BUTTON && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_BUTTON);
		}
		if (option_ == OPTION_VOLUME && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_VOLUME);
		}
	}
}

//描画
void OptionScene::Draw()
{
}

//開放
void OptionScene::Release()
{
}