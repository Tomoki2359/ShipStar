#include "OptionImage.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"

//コンストラクタ
OptionImage::OptionImage(GameObject* parent)
	: Button(parent, "OptionImage")
{
}

void OptionImage::InitialPoint()
{
	trans_[0].position_.x = -0.8f;
	trans_[0].position_.y = -0.8f;
}

void OptionImage::SetFile()
{
	fileName[0] = L"Assets\\BackButton.png";
}
void OptionImage::PutButton()
{
	SCENE_CHANGE(SCENE_ID_TITLE);
}