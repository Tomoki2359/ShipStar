#include "CustomScene.h"

//コンストラクタ
CustomScene::CustomScene(GameObject* parent)
	: GameObject(parent, "CustomScene"),mouseMoob_(true),custom_(-1),change_(false), first_(true)
{
}

//初期化
void CustomScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<OKButton>(this);
	Instantiate<BackButton>(this);
}

//更新
void CustomScene::Update()
{
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
		custom_++;
		mouseMoob_ = false;
		if (custom_ >= MAX_CUSTOM)
		{
			custom_ = CUSTOM_BACK;
		}
	}
	if (Input::IsKeyDown(DIK_W))
	{
		custom_--;
		mouseMoob_ = false;
		if (custom_ < 0)
		{
			custom_ = CUSTOM_OK;
		}
	}

	//マウスが動いたかどうか
	mousePos_ = mouseNext_;
	mouseNext_ = Input::GetMousePosition();
	if (mousePos_.x != mouseNext_.x && mousePos_.y != mouseNext_.y)
	{
		mouseMoob_ = true;
	}

	//変更するかどうか
	if (change_ == false)
	{
		if (FindObject("BackButton") == nullptr)
		{
			SCENE_CHANGE(SCENE_ID_LOBBY);
		}

		if (FindObject("OKButton") == nullptr)
		{
			Instantiate<OKButton>(this);
			first_ = true;
			change_ = true;
		}

		//キー操作
		if (mouseMoob_ == false)
		{
			if (custom_ == CUSTOM_BACK)
			{
				pBack_->IsButton();
			}
			if (custom_ == CUSTOM_OK)
			{
				pOK_->IsButton();
			}
		}
	}

	//本当に変更するかどうか
	if (change_ == true)
	{
		if (FindObject("BackButton") == nullptr)
		{
			Instantiate<BackButton>(this);
			first_ = true;
			change_ = false;
		}

		if (FindObject("OKButton") == nullptr)
		{
			Instantiate<OKButton>(this);
			first_ = true;
			change_ = false;
		}

		//キー操作
		if (mouseMoob_ == false)
		{
			if (custom_ == CUSTOM_BACK)
			{
				pBack_->IsButton();
			}
			if (custom_ == CUSTOM_OK)
			{
				pOK_->IsButton();
			}
		}
	}
}

//描画
void CustomScene::Draw()
{
}

//開放
void CustomScene::Release()
{
}