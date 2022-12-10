#include "ModeSelection.h"
#include "../Engine/Image.h"
#include "../Option.h"

//コンストラクタ
ModeSelection::ModeSelection(GameObject* parent)
	: Button(parent, "ModeSelection")
{
	SIZE = 4;
}

void ModeSelection::InitialPoint()
{
	trans_[0].position_ = XMFLOAT3{ 0, 0.7f ,0 };
	trans_[1].position_ = XMFLOAT3{ 0, 0.2f ,0 };
	trans_[2].position_ = XMFLOAT3{ 0, -0.3f ,0 };
	trans_[3].position_ = XMFLOAT3{ 0, -0.8f ,0 };
}

void ModeSelection::SetFile()
{
	fileName[0] = L"Assets\\Mode1.png";
	fileName[1] = L"Assets\\Mode2.png";
	fileName[2] = L"Assets\\Mode3.png";
	fileName[3] = L"Assets\\Mode4.png";
}

void ModeSelection::PutButton()
{
	if (trans_[0].scale_.x <= 0)
	{
		Option::SetMode(tucheNumber_);
		KillMe();
	}
	for (int i = 0; i < SIZE; i++)
	{
		trans_[i].scale_.x -= 0.1f;
		trans_[i].scale_.y -= 0.1f;
		trans_[i].scale_.z -= 0.1f;
	}
}

void ModeSelection::TucheButton(int number)
{
	trans_[number].scale_.x = 1.1f;
	trans_[number].scale_.y = 1.1f;
}
