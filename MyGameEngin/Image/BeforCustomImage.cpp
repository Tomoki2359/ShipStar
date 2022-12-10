#include "BeforCustomImage.h"
#include "../Engine/Image.h"
#include "../Option.h"
#include "../Engine/SceneManager.h"

//コンストラクタ
BeforCustomImage::BeforCustomImage(GameObject* parent)
	: Button(parent, "BeforCustomImage"), partsBrightness_(0.5f), isBrightness_(false),isNumber(-1)
{
	SIZE = 2;
	MODEL = 4;
}

void BeforCustomImage::InitialPoint()
{
	trans_[0].position_.x = -0.8f;
	trans_[0].position_.y = -0.8f;
	trans_[1].position_.x = 0.8f;
	trans_[1].position_.y = -0.8f;

}

void BeforCustomImage::SetFile()
{
	fileName[0] = L"Assets\\BackButton.png";
	fileName[1] = L"Assets\\OKButton.png";
}

void BeforCustomImage::FirstFind()
{
	pEngin_ = (EnginParts*)FindObject("EnginParts");
	assert(pEngin_ != nullptr);
	engineNum_ = pEngin_->GetParts();
	engineColor_ = pEngin_->GetColor();
	pBody_ = (BodyParts*)FindObject("BodyParts");
	assert(pBody_ != nullptr);
	bodyNum_ = pBody_->GetParts();
	bodyColor_ = pBody_->GetColor();
	pWing_ = (WingParts*)FindObject("WingParts");
	assert(pWing_ != nullptr);
	wingNum_ = pWing_->GetParts();
	wingColor_ = pWing_->GetColor();
	pCookpit_ = (CookpitParts*)FindObject("CookpitParts");
	assert(pCookpit_ != nullptr);
	cookpitNum_ = pCookpit_->GetParts();
	cookpitColor_ = pCookpit_->GetColor();

}

void BeforCustomImage::PutButton()
{
	if (tucheNumber_ == 0)
	{
		SCENE_CHANGE(SCENE_ID_LOBBY);
	}
	else if (tucheNumber_ == 1)
	{
		pParent_->SetPosition(XMFLOAT3{pParent_->GetPosition().x - 0.1f,0.0f,0.0f});
		if (pParent_->GetPosition().x <= -2)
		{
			pParent_->SetPosition(XMFLOAT3{ -2.0f,0.0f,0.0f });
		}
		else
		{
			return;
		}
	}
	isPut = false;
}

void BeforCustomImage::TucheButton(int number)
{
	if (isNumber != tucheNumber_)
	{
		partsBrightness_ = 0.5f;
		isBrightness_ = false;
	}
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
	if (tucheNumber_ == SIZE )
	{
		PartsChange(pEngin_, engineNum_, engineColor_);
		pEngin_->SetBrightness(partsBrightness_);

		pEngin_->Union((PARTS_NAME)bodyNum_, engineNum_);
		pWing_->Union((PARTS_NAME)bodyNum_, wingNum_);
		pCookpit_->Union((PARTS_NAME)bodyNum_, cookpitNum_);
	}
	if (tucheNumber_ == SIZE + 1)
	{
		PartsChange(pBody_, bodyNum_, bodyColor_);
		pBody_->SetBrightness(partsBrightness_);

		pEngin_->Union((PARTS_NAME)bodyNum_, engineNum_);
		pWing_->Union((PARTS_NAME)bodyNum_, wingNum_);
		pCookpit_->Union((PARTS_NAME)bodyNum_, cookpitNum_);
	}
	if (tucheNumber_ == SIZE + 2)
	{
		PartsChange(pWing_, wingNum_, wingColor_);
		pWing_->SetBrightness(partsBrightness_);

		pEngin_->Union((PARTS_NAME)bodyNum_, engineNum_);
		pWing_->Union((PARTS_NAME)bodyNum_, wingNum_);
		pCookpit_->Union((PARTS_NAME)bodyNum_, cookpitNum_);
	}
	if (tucheNumber_ == SIZE + 3)
	{
		PartsChange(pCookpit_, cookpitNum_, cookpitColor_);
		pCookpit_->SetBrightness(partsBrightness_);

		pEngin_->Union((PARTS_NAME)bodyNum_, engineNum_);
		pWing_->Union((PARTS_NAME)bodyNum_, wingNum_);
		pCookpit_->Union((PARTS_NAME)bodyNum_, cookpitNum_);
	}
}

bool BeforCustomImage::IsAddCondition()
{
	if (pParent_->GetPosition().x == 0)
	{
		return true;
	}
	return false;
}

void BeforCustomImage::PartsChange(Parts* parts, int& partsNum, int& partsColor)
{
	if (isBrightness_)
	{
		partsBrightness_ = partsBrightness_ - 0.01f;
		if (partsBrightness_ <= 0.5f)
		{
			isBrightness_ = false;
		}
	}
	else
	{
		partsBrightness_ = partsBrightness_ + 0.01f;
		if (partsBrightness_ >= 1.0f)
		{
			isBrightness_ = true;
		}
	}
	if (Input::IsKeyDown(DIK_D))
	{
		partsNum++;
	}
	if (Input::IsKeyDown(DIK_A))
	{
		partsNum--;
	}
	if (Input::IsKeyDown(DIK_Z))
	{
		partsColor++;
		if (partsColor >= 5)
		{
			partsColor = 0;
		}
	}
	if (partsNum < PARTS_GINGA)
	{
		partsNum = PARTS_END - 1;
	}
	if (partsNum >= PARTS_END)
	{
		partsNum = PARTS_GINGA;
	}
	parts->SetColor(partsColor);
	parts->SetParts(partsNum);
	parts->Load();
	parts->Union((PARTS_NAME)bodyNum_, partsNum);
}

void BeforCustomImage::SetParts()
{
	PARTS_NUM parts_;
	parts_.BODY = pBody_->GetPartsNum();
	parts_.COCKPIT = pCookpit_->GetPartsNum();
	parts_.ENGINE = pEngin_->GetPartsNum();
	parts_.WING = pWing_->GetPartsNum();
	Option::SetParts(parts_);
	Option::SetColor(engineColor_, PARTS_ENGINE);
	Option::SetColor(bodyColor_, PARTS_BODY);
	Option::SetColor(wingColor_, PARTS_WING);
	Option::SetColor(cookpitColor_, PARTS_COCKPIT);
}