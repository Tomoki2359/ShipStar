#include "Button.h"
#include "../Engine/Image.h"
#include "../Engine/Camera.h"

//コンストラクタ
Button::Button(GameObject* parent, std::string name)
	: GameObject(parent, name),change_(false), MousePos_(),alpha_(255),isPut(false),SIZE(1)
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
	SetFile();
	for (short i = 0; i < SIZE; i++)
	{
		hPict_[i] = Image::Load(fileName[i]);
	}
	InitialPoint();
}

//更新
void Button::Update()
{
	//マウスの位置の取得
	MousePos_ = Input::GetMousePosition();

	//押されたかどうか
	if (isPut == false)
	{
		//画像の位置
		if (IsImage() || change_)
		{
			TucheButton();
			if (Input::IsMouceDown(0) || Input::IsKeyDown(DIK_Z))
				isPut = true;
		}
		else
		{
			transform_.scale_.x = 1.0f;
			transform_.scale_.y = 1.0f;
		}
	}
	else
	{
		PutButton();
	}
	change_ = false;
}

//描画
void Button::Draw()
{
	for (int i = 0; i < SIZE; i++)
	{
		Image::SetTransform(hPict_[i], transform_);
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
	change_ = true;
}

bool Button::IsImage()
{
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
	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = 0.0f;

	//マウス位置(奥)
	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0f;

	//① mousePosFrontをベクトルに変換
	XMVECTOR vMousePosFront = XMLoadFloat3(&mousePosFront);
	//② ①にinvVP,invPrj,invViewをかける
	vMousePosFront = XMVector3TransformCoord(vMousePosFront, invVP);
	//③ mousePosBackをベクトルに変換
	XMVECTOR vMousePosBack = XMLoadFloat3(&mousePosBack);
	//④ ③にinvVP, invPrj, invViewをかける
	vMousePosBack = XMVector3TransformCoord(vMousePosBack, invVP);

	//⑤ ②から④に向かってレイをうつ(とりあえずモデル番号はhModel_[0])
	RayCastData MousePos;
	XMStoreFloat3(&MousePos.start, vMousePosFront);

	XMStoreFloat3(&MousePos.dir, vMousePosBack - vMousePosFront);
	for (int i = 0; i < SIZE; i++)
	{
		Image::SetTransform(hPict_[i], transform_);
		Image::RayCast(hPict_[i], &MousePos);
		if (MousePos.hit)
		{
			return true;
		}
	}
	return false;
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

void Button::TucheButton()
{
	transform_.scale_.x = 1.1f;
	transform_.scale_.y = 1.1f;
}
