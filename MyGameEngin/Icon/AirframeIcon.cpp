#include "AirframeIcon.h"
#include "../Engine/Image.h"

//コンストラクタ
AirframeIcon::AirframeIcon(GameObject* parent, std::string name)
	: GameObject(parent, name),hPict_(-1)
{
}

AirframeIcon::AirframeIcon(GameObject* parent)
	: AirframeIcon(parent, "AirframeIcon")
{
}

//初期化
void AirframeIcon::Initialize()
{
	Load();
	InitialPos_ = XMFLOAT3(0.9f, 0.65f, 0);
	transform_.position_ = InitialPos_;
}

//更新
void AirframeIcon::Update()
{
	AirframePos();

	transform_.position_ = XMFLOAT3((InitialPos_.x + (AirframePos_.x / 2100)), InitialPos_.y - (AirframePos_.z / 1200), 0);
}

//描画
void AirframeIcon::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void AirframeIcon::Release()
{
}