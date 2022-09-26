#include "Button.h"
#include "../Engine/Image.h"
#include "../Engine/Camera.h"

//コンストラクタ
Button::Button(GameObject* parent, std::string name)
	: GameObject(parent, name), hPict_(-1), change_(false), MousePos_()
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
	Image::SetTransform(hPict_, transform_);
	Image::RayCast(hPict_, &MousePos);
	if (MousePos.hit)
	{
		return true;
	}
	return false;
}
