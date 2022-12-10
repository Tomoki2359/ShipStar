#include "OptionVolume.h"

//コンストラクタ
OptionVolume::OptionVolume(GameObject* parent)
	: Button(parent, "OptionVolume")
{
}

void OptionVolume::InitialPoint()
{
	trans_[0].position_.y = -0.25f;
}

void OptionVolume::SetFile()
{
	fileName[0] = L"Assets\\OptionVolume.png";
}
