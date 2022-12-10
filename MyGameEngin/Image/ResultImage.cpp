#include "ResultImage.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"

//コンストラクタ
ResultImage::ResultImage(GameObject* parent)
	: Button(parent, "ResultImage")
{
	SIZE = 2;
}

void ResultImage::InitialPoint()
{
	trans_[0].position_.x = -0.8f;
	trans_[0].position_.y = -0.8f;
	trans_[1].position_.x = 0.8f;
	trans_[1].position_.y = -0.8f;
}

void ResultImage::SetFile()
{
	fileName[0] = L"Assets\\BackButton.png";
	fileName[1] = L"Assets\\retry.png";
}

void ResultImage::PutButton()
{
	if (tucheNumber_ == 0)
	{
		SCENE_CHANGE(SCENE_ID_LOBBY);
	}
	else if (tucheNumber_ == 1)
	{
		SCENE_CHANGE(SCENE_ID_PLAY);
	}
}