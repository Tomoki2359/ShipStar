#include "LobbyBackground.h"
#include "../Engine/Image.h"
#include "../Player.h"

//コンストラクタ
LobbyBackground::LobbyBackground(GameObject* parent)
	: GameObject(parent, "LobbyBackground"), hPict_(-1)
{
}

//初期化
void LobbyBackground::Initialize()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\LobbyBackground.png");
	assert(hPict_ >= 0);
	Image::IsDifference(hPict_,false);
}

//更新
void LobbyBackground::Update()
{
}

//描画
void LobbyBackground::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void LobbyBackground::Release()
{
}