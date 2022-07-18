#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
//コンストラクタ
SplashScene::SplashScene(GameObject* parent)
	: GameObject(parent, "SplashScene"), startTime_(35), change_(290),alpha_(0),time_(0), hPict_{ -1 ,-1 }
{
}

//初期化
void SplashScene::Initialize()
{
	//チームロゴ
	hPict_[0] = Image::Load(L"Assets\\TeamLogo.png");
	assert(hPict_[0] >= 0);

	//学校ロゴ
	hPict_[1] = Image::Load(L"Assets\\SchoolLogo.png");
	assert(hPict_[1] >= 0);
	SetScreen(255, 255, 255);
	Image::SetAlpha(hPict_[0], 0);
}

//更新
void SplashScene::Update()
{
	time_++;
	//チームのロゴの表示
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

	//学校のロゴの表示
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

	//タイトルシーンへ
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

//描画
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

//開放
void SplashScene::Release()
{
}