#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
//�R���X�g���N�^
SplashScene::SplashScene(GameObject* parent)
	: GameObject(parent, "SplashScene"), startTime_(35), change_(290),alpha_(0),time_(0), hPict_{ -1 ,-1 }
{
}

//������
void SplashScene::Initialize()
{
	//�`�[�����S
	hPict_[0] = Image::Load(L"Assets\\TeamLogo.png");
	assert(hPict_[0] >= 0);

	//�w�Z���S
	hPict_[1] = Image::Load(L"Assets\\SchoolLogo.png");
	assert(hPict_[1] >= 0);
	SetScreen(255, 255, 255);
	Image::SetAlpha(hPict_[0], 0);
}

//�X�V
void SplashScene::Update()
{
	time_++;
	//�`�[���̃��S�̕\��
	if (time_ <= change_)
	{
		Image::SetAlpha(hPict_[0], alpha_);
		if (startTime_ < time_ && time_ <= startTime_ + 80)
		{
			alpha_ = alpha_ + 4;
		}

		if (time_ >= startTime_ + 170)
		{
			alpha_ = alpha_ - 4;
			SetScreen(alpha_, alpha_, alpha_);
		}
	}

	//�w�Z�̃��S�̕\��
	if (time_ > change_)
	{
		Image::SetAlpha(hPict_[1], alpha_);
		if (time_ <= change_ + 80)
		{
			alpha_ = alpha_ + 4;
		}

		if (time_ >= change_ + 170)
		{
			alpha_ = alpha_ - 4;
		}
	}

	//�^�C�g���V�[����
	if (time_ >= change_ * 2 - startTime_)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}

	if (alpha_ >= 255)
	{
		alpha_ = 255;
	}

	if (alpha_ <= 0)
	{
		alpha_ = 0;
	}
}

//�`��
void SplashScene::Draw()
{
	if (time_ <= change_)
	{
		Image::SetTransform(hPict_[0], transform_);
		Image::Draw(hPict_[0]);
	}
	if (time_ > change_)
	{
		Image::SetTransform(hPict_[1], transform_);
		Image::Draw(hPict_[1]);
	}
}

//�J��
void SplashScene::Release()
{
}