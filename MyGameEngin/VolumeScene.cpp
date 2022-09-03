#include "VolumeScene.h"


//コンストラクタ
VolumeScene::VolumeScene(GameObject* parent)
	: GameObject(parent, "VolumeScene"),mouseMoob_(false),volume_(-1), first_(true)
{
}

//初期化
void VolumeScene::Initialize()
{
	Instantiate<BackButton>(this);
	Instantiate<OKButton>(this);
	SetScreen(0, 0, 0);
}

//更新
void VolumeScene::Update()
{
	//画像のポインタを指定したかどうか
	if (first_)
	{
		first_ = false;
		pBack_ = (BackButton*)FindObject("BackButton");
		assert(pBack_ != nullptr);
		pOK_ = (OKButton*)FindObject("OKButton");
		assert(pOK_ != nullptr);
	}
	if (Input::IsKeyDown(DIK_S))
	{
		mouseMoob_ = false;
		volume_++;
		if (volume_ >= MAX_VOLUME)
		{
			volume_ = VOLUME_BACK;
		}
	}
	if (Input::IsKeyDown(DIK_W))
	{
		mouseMoob_ = false;
		volume_--;
		if (volume_ < 0)
		{
			volume_ = VOLUME_OK;
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
		if (volume_ == VOLUME_BACK)
		{
			pBack_->IsButton();
		}
		if (volume_ == VOLUME_OK)
		{
			pOK_->IsButton();
		}
	}
}

//描画
void VolumeScene::Draw()
{
}

//開放
void VolumeScene::Release()
{
}