#include "LobbyScene.h"
#include "Engine/Image.h"
#include "Image/LobbyBackground.h"
#include "Image/LobbyImage.h"

//コンストラクタ
LobbyScene::LobbyScene(GameObject* parent)
	: GameObject(parent, "LobbyScene"),alpha(0),start_(true)//,mouseMoob_(true),lobby_(-1), first_(true)
{
}

//初期化
void LobbyScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<LobbyBackground>(this);
	Instantiate<LobbyImage>(this);
	/*Instantiate<LobbyCourse>(this);
	Instantiate<LobbyCustom>(this);
	Instantiate<LobbyPlay>(this);*/
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
	//if (first_)
	//{
	//	first_ = false;
	//	pCourse_ = (LobbyCourse*)FindObject("LobbyCourse");
	//	assert(pCourse_ != nullptr);
	//	pPlay_ = (LobbyPlay*)FindObject("LobbyPlay");
	//	assert(pPlay_ != nullptr);
	//	pCustom_ = (LobbyCustom*)FindObject("LobbyCustom");
	//	assert(pCustom_ != nullptr);
	//}
	//if (Input::IsKeyDown(DIK_S))
	//{
	//	mouseMoob_ = false;
	//	lobby_++;
	//	if (lobby_ >= MAX_LOBBY)
	//	{
	//		lobby_ = LOBBY_COURSE;
	//	}
	//}
	//if (Input::IsKeyDown(DIK_W))
	//{
	//	mouseMoob_ = false;
	//	lobby_--;
	//	if (lobby_ < 0)
	//	{
	//		lobby_ = LOBBY_CUSTOM;
	//	}
	//}

	////マウスが動いたかどうか
	//mousePos_ = mouseNext_;
	//mouseNext_ = Input::GetMousePosition();
	//if (mousePos_.x != mouseNext_.x && mousePos_.y != mouseNext_.y)
	//{
	//	mouseMoob_ = true;
	//}

	//if (FindObject("LobbyPlay") == nullptr)
	//{
	//		SCENE_CHANGE(SCENE_ID_MATCHING);
	//}
	//

	//if (FindObject("LobbyCustom") == nullptr)
	//{
	//		SCENE_CHANGE(SCENE_ID_CUSTOM);
	//}

	////キー操作
	//if (mouseMoob_ == false)
	//{
	//	if (lobby_ == LOBBY_COURSE)
	//	{
	//		pCourse_->IsButton();
	//	}
	//	if (lobby_ == LOBBY_PLAY)
	//	{
	//		pPlay_->IsButton();
	//	}
	//	if (lobby_ == LOBBY_CUSTOM)
	//	{
	//		pCustom_->IsButton();
	//	}
	//}
}

//描画
void LobbyScene::Draw()
{
}

//開放
void LobbyScene::Release()
{
}