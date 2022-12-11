#include "LobbyScene.h"
#include "Engine/Image.h"
#include "Image/LobbyBackground.h"
#include "Image/LobbyImage.h"

//コンストラクタ
LobbyScene::LobbyScene(GameObject* parent)
	: GameObject(parent, "LobbyScene"),alpha(0),start_(true)
{
}

//初期化
void LobbyScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<LobbyBackground>(this);
	Instantiate<LobbyImage>(this);
	Image::AllSetAlpha(0);
}

//更新
void LobbyScene::Update()
{
	if (start_)
	{
		if (alpha == UINT8_MAX)
		{
			start_ = false;
		}
		Image::AllSetAlpha(alpha);
		alpha += 2;
	}
}

//描画
void LobbyScene::Draw()
{
}

//開放
void LobbyScene::Release()
{
}