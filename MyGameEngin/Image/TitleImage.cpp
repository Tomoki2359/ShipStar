#include "TitleImage.h"
#include "../Engine/Image.h"
#include "../Option.h"
#include "../Engine/SceneManager.h"

//コンストラクタ
TitleImage::TitleImage(GameObject* parent)
	: Button(parent, "TitleImage"),alpha(255)
{
	SIZE = 2;
}

void TitleImage::InitialPoint()
{
	trans_[0].position_.y = -0.25f;
	trans_[1].position_.y = -0.5f;
}

void TitleImage::SetFile()
{
	fileName[0] = L"Assets\\TitleStart.png";
	fileName[1] = L"Assets\\TitleOption.png";
}

void TitleImage::PutButton()
{
	Image::AllSetAlpha(alpha);
	if (tucheNumber_ == 0 && alpha <= 0)
	{
		SCENE_CHANGE(SCENE_ID_LOBBY);
	}
	else if (tucheNumber_ == 1 && alpha <= 0)
	{
		SCENE_CHANGE(SCENE_ID_OPTION);
	}
	alpha -= 2;
}