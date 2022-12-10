#include "MatchingScene.h"
#include "Image/MatchingCourse.h"
#include "Image/MatchingBackground.h"
#include "Image/MatchingImage.h"

//コンストラクタ
MatchingScene::MatchingScene(GameObject* parent)
	: GameObject(parent, "MatchingScene")//,mouseMoob_(true),matching_(-1), first_(true)
{
}

//初期化
void MatchingScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<MatchingBackground>(this);
	//Instantiate<BackButton>(this);
	//Instantiate<MatchingStart>(this);
	Instantiate<MatchingCourse>(this);
	Instantiate<MatchingImage>(this);
}

//更新
void MatchingScene::Update()
{
	//if (first_)
	//{
	//	first_ = false;
	//	pBack_ = (BackButton*)FindObject("BackButton");
	//	assert(pBack_ != nullptr);
	//	pStart_ = (MatchingStart*)FindObject("MatchingStart");
	//	assert(pStart_ != nullptr);
	//}
	//if (Input::IsKeyDown(DIK_S))
	//{
	//	matching_++;
	//	mouseMoob_ = false;
	//	if (matching_ >= MAX_MATCHING)
	//	{
	//		matching_ = MATCHING_BACK;
	//	}
	//}
	//if (Input::IsKeyDown(DIK_W))
	//{
	//	matching_--;
	//	mouseMoob_ = false;
	//	if (matching_ < 0)
	//	{
	//		matching_ = MATCHING_STRAT;
	//	}
	//}

	////マウスが動いたかどうか
	//mousePos_ = mouseNext_;
	//mouseNext_ = Input::GetMousePosition();
	//if (mousePos_.x != mouseNext_.x && mousePos_.y != mouseNext_.y)
	//{
	//	mouseMoob_ = true;
	//}

	//if (FindObject("BackButton") == nullptr)
	//{
	//	SCENE_CHANGE(SCENE_ID_LOBBY);
	//}

	//if (FindObject("MatchingStart") == nullptr)
	//{
	//	SCENE_CHANGE(SCENE_ID_PLAY);
	//}
	//
	////キー操作
	//if (mouseMoob_ == false)
	//{
	//	if (matching_ == MATCHING_BACK)
	//	{
	//		pBack_->IsButton();
	//	}
	//	if (matching_ == MATCHING_STRAT)
	//	{
	//		pStart_->IsButton();
	//	}
	//}
}

//描画
void MatchingScene::Draw()
{
}

//開放
void MatchingScene::Release()
{
}