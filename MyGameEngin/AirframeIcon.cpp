#include "AirframeIcon.h"
#include "Engine/Image.h"

//コンストラクタ
AirframeIcon::AirframeIcon(GameObject* parent, std::string name)
	: GameObject(parent, name), hPict_(-1)
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
}

//更新
void AirframeIcon::Update()
{
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