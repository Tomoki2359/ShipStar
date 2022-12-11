#include "AfterCustomImage.h"
#include "../Engine/Image.h"
#include "../Engine/Model.h"
#include "../Option.h"
#include "../Engine/SceneManager.h"
#include "BeforCustomImage.h"


//コンストラクタ
AfterCustomImage::AfterCustomImage(GameObject* parent)
	: Button(parent, "AfterCustomImage"), difference_({0.0f,0.0f,0.0f})
{
	SIZE = 2;
}

void AfterCustomImage::InitialPoint()
{
	trans_[0].position_.x = 1.2f;
	trans_[0].position_.y = -0.8f;
	trans_[1].position_.x = 2.8f;
	trans_[1].position_.y = -0.8f;

}

void AfterCustomImage::SetFile()
{
	fileName[0] = L"Assets\\BackButton.png";
	fileName[1] = L"Assets\\FixeButton.png";
}

void AfterCustomImage::PutButton()
{
	if (tucheNumber_ == 0)
	{
		difference_.x += 0.1f;
		Image::AllTransPosition(difference_);
		if (difference_.x >= 0.0f)
		{
			difference_.x = 0.0f;
			Image::AllTransPosition(difference_);
			isPut = false;
		}
		return;
	}
	Image::AllSetAlpha(alpha);
	Model::AllSetAlpha(alpha);
	if (tucheNumber_ == 1 && alpha <= 0)
	{
		BeforCustomImage* pBefor_;
		pBefor_ = (BeforCustomImage*)FindObject("BeforCustomImage");
		assert(pBefor_ != nullptr);
		pBefor_->SetParts();
		SCENE_CHANGE(SCENE_ID_LOBBY);
	}
	alpha -= 2;
}

void AfterCustomImage::TucheButton(int number)
{
	if (tucheNumber_ == 0)
	{
		trans_[0].scale_.x = 1.1f;
		trans_[0].scale_.y = 1.1f;
	}
	if (tucheNumber_ == 1)
	{
		trans_[1].scale_.x = 1.1f;
		trans_[1].scale_.y = 1.1f;
	}
}

bool AfterCustomImage::IsAddCondition()
{
	difference_.x = Image::GetDifference().x;
	alpha = Image::GetAlpha(hPict_[0]);
	if (difference_.x <= -2.0f)
	{
		return true;
	}
	return false;
}