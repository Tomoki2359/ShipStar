#include "MatchingImage.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"

//コンストラクタ
MatchingImage::MatchingImage(GameObject* parent)
	: Button(parent, "MatchingImage")
{
	SIZE = 2;
}

void MatchingImage::InitialPoint()
{
	trans_[0].position_.y = -0.25f;
	trans_[1].position_.x = -0.8f;
	trans_[1].position_.y = -0.8f;
}

void MatchingImage::SetFile()
{
	fileName[0] = L"Assets\\MatchingStart.png";
	fileName[1] = L"Assets\\BackButton.png";
}

void MatchingImage::PutButton()
{
	if (tucheNumber_ == 0)
	{
		SCENE_CHANGE(SCENE_ID_PLAY);
	}
	else if (tucheNumber_ == 1)
	{
		SCENE_CHANGE(SCENE_ID_LOBBY);
	}
}