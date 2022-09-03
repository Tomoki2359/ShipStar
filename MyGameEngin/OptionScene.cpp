#include "OptionScene.h"

//コンストラクタ
OptionScene::OptionScene(GameObject* parent)
	: GameObject(parent, "OptionScene"), mouseMoob_(true), option_(-1), first_(true)
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
	if (first_)
	{
		first_ = false;
		pBack_ = (BackButton*)FindObject("BackButton");
		assert(pBack_ != nullptr);
		pButton_ = (OptionButton*)FindObject("OptionButton");
		assert(pButton_ != nullptr);
		pVolume_ = (OptionVolume*)FindObject("OptionVolume");
		assert(pVolume_ != nullptr);
	}
	if (Input::IsKeyDown(DIK_S))
	{
		mouseMoob_ = false;
		option_++;
		if (option_ >= MAX_OPTION)
		{
			option_ = OPTION_BACK;
		}
	}
	if (Input::IsKeyDown(DIK_W))
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
		if (option_ == OPTION_BACK)
		{
			pBack_->IsButton();
		}
		if (option_ == OPTION_BUTTON)
		{
			pButton_->IsButton();
		}
		if (option_ == OPTION_VOLUME)
		{
			pVolume_->IsButton();
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