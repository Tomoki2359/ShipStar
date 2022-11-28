#include "ResultScene.h"
#include "Image/MatchingBackground.h"
#include "Engine/Time.h"
#include "Option.h"

//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene"), mouseMoob_(true), result_(-1), first_(true),
	pBack_(nullptr), pOK_(nullptr), mouseNext_(), mousePos_()
{
}

//������
void ResultScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<MatchingBackground>(this);
	Instantiate<BackButton>(this);
	Instantiate<RetryButton>(this);
	transform_.position_ = XMFLOAT3(0, 0, 0);
	transform_.rotate_ = XMFLOAT3(0, 0, 0);
	transform_.scale_ = XMFLOAT3(1, 1, 1);
}

//�X�V
void ResultScene::Update()
{
	if (first_)
	{
		first_ = false;
		pBack_ = (BackButton*)FindObject("BackButton");
		//assert(pBack_ != nullptr);
		pOK_ = (RetryButton*)FindObject("RetryButton");
		//assert(pOK_ != nullptr);
	}
	if (Input::IsKeyDown(DIK_S))
	{
		result_++;
		mouseMoob_ = false;
		if (result_ >= MAX_RESULT)
		{
			result_ = RESULT_BACK;
		}
	}
	if (Input::IsKeyDown(DIK_W))
	{
		result_--;
		mouseMoob_ = false;
		if (result_ < 0)
		{
			result_ = RESULT_OK;
		}
	}

	//�}�E�X�����������ǂ���
	mousePos_ = mouseNext_;
	mouseNext_ = Input::GetMousePosition();
	if (mousePos_.x != mouseNext_.x && mousePos_.y != mouseNext_.y)
	{
		mouseMoob_ = true;
	}

	if (FindObject("BackButton") == nullptr)
	{
		SCENE_CHANGE(SCENE_ID_LOBBY);
	}

	if (FindObject("RetryButton") == nullptr)
	{
		Option::SetMode(MODE_REPLAY);
		SCENE_CHANGE(SCENE_ID_PLAY);
	}

	//�L�[����
	if (mouseMoob_ == false)
	{
		if (result_ == RESULT_BACK)
		{
			pBack_->IsButton();
		}
		if (result_ == RESULT_OK)
		{
			pOK_->IsButton();
		}
	}
}

//�`��
void ResultScene::Draw()
{
	Time::GetTime();
}

//�J��
void ResultScene::Release()
{
	SAFE_RELEASE(pBack_);
	SAFE_RELEASE(pOK_);
}