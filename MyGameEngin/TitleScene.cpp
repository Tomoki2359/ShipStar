#include "TitleScene.h"
#include "Engine/Input.h"
#include "Image/TitleName.h"
#include "Image/Background.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), mouseMoob_(true), title_(-1), first_(true)
{
}

//������
void TitleScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<TitleName>(this);
	Instantiate<TitleStart>(this);
	Instantiate<TitleOption>(this);
	Instantiate<Background>(this);
}

//�X�V
void TitleScene::Update()
{
	if (first_)
	{
		first_ = false;
		pStart_ = (TitleStart*)FindObject("TitleStart");
		assert(pStart_ != nullptr);
		pOption_ = (TitleOption*)FindObject("TitleOption");
		assert(pOption_ != nullptr);
	}

	if (Input::IsKeyDown(DIK_S))
	{
		mouseMoob_ = false;
		title_++;
		if (title_ >= MAX_TITLE)
		{
			title_ = TITLE_START;
		}
	}
	if (Input::IsKeyDown(DIK_W))
	{
		mouseMoob_ = false;
		title_--;
		if (title_ < 0)
		{
			title_ = TITLE_OPTION;
		}
	}

	//�}�E�X�����������ǂ���
	mousePos_ = mouseNext_;
	mouseNext_ = Input::GetMousePosition();
	if (mousePos_.x != mouseNext_.x && mousePos_.y != mouseNext_.y)
	{
		mouseMoob_ = true;
	}

	if (FindObject("TitleStart") == nullptr)
	{ 
			SCENE_CHANGE(SCENE_ID_LOBBY);
	}

	if (FindObject("TitleOption") == nullptr)
	{
			SCENE_CHANGE(SCENE_ID_OPTION);
	}

	//�L�[����
	if (mouseMoob_ == false)
	{
		if (title_ == TITLE_START)
		{
			pStart_->IsButton();
		}
		if (title_ == TITLE_OPTION)
		{
			pOption_->IsButton();
		}
	}
	//SCENE_CHANGE(SCENE_ID_PLAY);
}

//�`��
void TitleScene::Draw()
{
}

//�J��
void TitleScene::Release()
{
}