#include "Button.h"
#include "../Engine/Image.h"
#include "../Engine/Camera.h"

//コンストラクタ
Button::Button(GameObject* parent, std::string name)
	: GameObject(parent, name), MousePos_(),alpha_(255),isPut(false),SIZE(1),MODEL(0),first_(true),tucheNumber_(-1)
{
}

Button::Button(GameObject* parent)
	: Button(parent, "Button")
{
}

//初期化
void Button::Initialize()
{
	//モデルデータのロード
	hPict_ = new short[SIZE];
	fileName = new LPCWSTR[SIZE];
	change_ = new bool[SIZE + MODEL];
	trans_ = new Transform[SIZE];
	SetFile();
	for (short i = 0; i < SIZE; i++)
	{
		hPict_[i] = Image::Load(fileName[i]);
		change_[i] = false;
	}
	for (short i = 0; i < MODEL; i++)
	{
		change_[i + SIZE] = false;
	}
	InitialPoint();
}

//更新
void Button::Update()
{
	//一度だけしたい処理
	if (first_)
	{
		FirstFind();
		first_ = false;
	}
	//押されたかどうか
	if (isPut == false)
	{
		//キー操作
		IsKey();
		//画像の位置
		IsImage();
		for (int i = 0; i < SIZE + MODEL; i++)
		{
			if (change_[i] && IsAddCondition())
			{
				TucheButton(i);
				if (Input::IsMouceDown(0) || Input::IsKeyDown(DIK_Z))
				{
					tucheNumber_ = i;
					isPut = true;
				}
			}
			else
			{
				NoTucheButton(i);
			}
		}
	}
	else
	{
		PutButton();
	}
}

//描画
void Button::Draw()
{
	for (int i = 0; i < SIZE; i++)
	{
		Transform trans;
		trans = trans_[i];
		trans.position_.x = trans.position_.x + pParent_->GetPosition().x;
		trans.position_.y = trans.position_.y + pParent_->GetPosition().y;
		Image::SetTransform(hPict_[i], trans);
		Image::Draw(hPict_[i]);
	}
}

//開放
void Button::Release()
{
}

//選択されているかどうか
void Button::IsButton()
{
	change_[0] = true;
}

//複数画像がある場合
void Button::IsButton(int number)
{
	change_[number] = true;
}

void Button::IsImage()
{
	XMFLOAT3 previousMousePos_ = MousePos_;
	MousePos_ = Input::GetMousePosition();
	if (MousePos_.x != previousMousePos_.x && MousePos_.y !=  previousMousePos_.y)
	{
		change_[tucheNumber_] = false;
		//マウスの位置の取得
		MousePos_ = Input::GetMousePosition();
		//ビューポート行列
		float w = (float)Direct3D::scrWidth / 2.0f;
		float h = (float)Direct3D::scrHeight / 2.0f;
		XMMATRIX vp = {
			w, 0,0,0,
			0,-h,0,0,
			0, 0,1,0,
			w, h,0,1
		};

		//各行列の逆行列
		XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
		XMMATRIX invPrj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
		XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

		//マウス位置(手前)
		XMFLOAT3 mousePosFront = MousePos_;
		mousePosFront.z = 0.0f;

		//マウス位置(奥)
		XMFLOAT3 mousePosBack = MousePos_;
		mousePosBack.z = 1.0f;

		XMVECTOR vMousePosFront = XMLoadFloat3(&mousePosFront);
		vMousePosFront = XMVector3TransformCoord(vMousePosFront, invVP);
		XMVECTOR vMousePosBack = XMLoadFloat3(&mousePosBack);
		vMousePosBack = XMVector3TransformCoord(vMousePosBack, invVP);

		RayCastData MousePos;
		XMStoreFloat3(&MousePos.start, vMousePosFront);

		XMStoreFloat3(&MousePos.dir, vMousePosBack - vMousePosFront);
		for (int i = 0; i < SIZE; i++)
		{
			Image::RayCast(hPict_[i], &MousePos);
			change_[i] = MousePos.hit;
		}
	}
}

void Button::IsKey()
{
	if (Input::IsKeyDown(DIK_S))
	{
		change_[tucheNumber_] = false;
		tucheNumber_++;
		if (tucheNumber_ >= SIZE + MODEL || tucheNumber_ < 0)
		{
			tucheNumber_ = 0;
		}
		change_[tucheNumber_] = true;
	}
	else if (Input::IsKeyDown(DIK_W))
	{
		change_[tucheNumber_] = false;
		tucheNumber_--;
		if (tucheNumber_ < 0 || tucheNumber_ >= SIZE + MODEL)
		{
			tucheNumber_ = SIZE + MODEL - 1;
		}
		change_[tucheNumber_] = true;
	}
}

//押した時どうするか
void Button::PutButton()
{
	//画像が見えなくなってから消す
	//if (alpha_ <= 0)
	//{
		KillMe();
	//}
	//alpha_ -= 3;
	//Image::AllSetAlpha(alpha_);
}

void Button::TucheButton(int number)
{
	trans_[number].scale_.x = 1.1f;
	trans_[number].scale_.y = 1.1f;
}

void Button::NoTucheButton(int number)
{
	trans_[number].scale_.x = 1.0f;
	trans_[number].scale_.y = 1.0f;
}
