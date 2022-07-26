#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
//�R���X�g���N�^
SplashScene::SplashScene(GameObject* parent)
	: GameObject(parent, "SplashScene"), startTime_(35), change_(290),alpha_(0),time_(0), MoveAlpha_(4), hPict_{ -1 ,-1 }
{
}

//������
void SplashScene::Initialize()
{
	//�`�[�����S
	hPict_[LOGO_TEAM] = Image::Load(L"Assets\\TeamLogo.png");
	assert(hPict_[LOGO_TEAM] >= 0);

	//�w�Z���S
	hPict_[LOGO_SCHOOL] = Image::Load(L"Assets\\SchoolLogo.png");
	assert(hPict_[LOGO_SCHOOL] >= 0);
	SetScreen(UINT8_MAX, UINT8_MAX, UINT8_MAX);
	Image::SetAlpha(hPict_[LOGO_TEAM], 0);
}

//�X�V
void SplashScene::Update()
{
	time_++;
	//�`�[���̃��S�̕\��
	if (time_ <= change_)
	{
		Image::SetAlpha(hPict_[LOGO_TEAM], alpha_);
		if (startTime_ < time_ && time_ <= startTime_ + 80)
		{
			alpha_ = alpha_ + MoveAlpha_;
		}

		if (time_ >= startTime_ + 170)
		{
			alpha_ = alpha_ - MoveAlpha_;
			SetScreen(alpha_, alpha_, alpha_);
		}
	}

	//�w�Z�̃��S�̕\��
	if (time_ > change_)
	{
		Image::SetAlpha(hPict_[LOGO_SCHOOL], alpha_);
		if (time_ <= change_ + 80)
		{
			alpha_ = alpha_ + MoveAlpha_;
		}

		if (time_ >= change_ + 170)
		{
			alpha_ = alpha_ - MoveAlpha_;
		}
	}

	//�^�C�g���V�[����
	if (time_ >= change_ * 2 - startTime_)
	{
		SCENE_CHANGE(SCENE_ID_TITLE);
	}

	if (alpha_ >= UINT8_MAX)	//256�ȏ�ɂ͂Ȃ�Ȃ��悤�ɂ���
	{
		alpha_ = UINT8_MAX;
	}

	if (alpha_ <= NULL)			//0�����ɂ͂Ȃ�Ȃ��悤�ɂ���
	{
		alpha_ = NULL;
	}
}

//�`��
void SplashScene::Draw()
{
	if (time_ <= change_)
	{
		Image::SetTransform(hPict_[LOGO_TEAM], transform_);
		Image::Draw(hPict_[LOGO_TEAM]);
	}
	if (time_ > change_)
	{
		Image::SetTransform(hPict_[LOGO_SCHOOL], transform_);
		Image::Draw(hPict_[LOGO_SCHOOL]);
	}
}

//�J��
void SplashScene::Release()
{
}