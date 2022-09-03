#include "Button.h"
#include "../Engine/Image.h"
//コンストラクタ
Button::Button(GameObject* parent)
	: GameObject(parent, "Button"), hPict_(-1), change_(false)
{
}
Button::Button(GameObject* parent, std::string name)
	: GameObject(parent, name), hPict_(-1), change_(false)
{
}

//初期化
void Button::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(SetFile());
	assert(hPict_ >= 0);
	InitialPoint();
}

//更新
void Button::Update()
{
	//マウスの位置の取得
	MousePos_ = Input::GetMousePosition();

	//画像の位置
	if (IsImage() || change_ )
	{
		transform_.scale_.x = 1.1f;
		transform_.scale_.y = 1.1f;
		if (Input::IsMouceDown(0) || Input::IsKeyDown(DIK_Z))
			KillMe();
	}
	else
	{
		transform_.scale_.x = 1.0f;
		transform_.scale_.y = 1.0f;
	}

	change_ = false;
}

//描画
void Button::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void Button::Release()
{
}

//選択されているかどうか
void Button::IsButton()
{
	change_ = true;
}
