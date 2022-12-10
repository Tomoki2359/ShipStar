#include "LobbyImage.h"
#include "../Engine/Image.h"
#include "../Option.h"
#include "../Engine/SceneManager.h"
#include "ModeSelection.h"

//コンストラクタ
LobbyImage::LobbyImage(GameObject* parent)
	: Button(parent, "LobbyImage")
{
	SIZE = 3;
}

void LobbyImage::InitialPoint()
{
	trans_[0].position_.x = -0.7f;
	trans_[0].position_.y = 0.7f;
	trans_[1].position_.x = 0.7f;
	trans_[1].position_.y = 0.7f;
	trans_[2].position_.x = 0.7f;
	trans_[2].position_.y = -0.7f;
}

void LobbyImage::SetFile()
{
	fileName[0] = L"Assets\\LobbyCourse.png";
	fileName[1] = L"Assets\\LobbyPlay.png";
	fileName[2] = L"Assets\\LobbyCustom.png";
}

void LobbyImage::PutButton()
{
	if (tucheNumber_ == 0)
	{
		trans_[0].scale_.x = 1.0f;
		trans_[0].scale_.y = 1.0f;
		Instantiate<ModeSelection>(this);
		isPut = false;
	}
	else if (tucheNumber_ == 1)
	{
		SCENE_CHANGE(SCENE_ID_MATCHING);
	}
	else if (tucheNumber_ == 2)
	{
		SCENE_CHANGE(SCENE_ID_CUSTOM);
	}
}

bool LobbyImage::IsAddCondition()
{
	if (FindObject("ModeSelection") == nullptr)
	{
		return true;
	}
	return false;
}