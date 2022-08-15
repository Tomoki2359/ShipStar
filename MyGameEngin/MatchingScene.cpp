#include "MatchingScene.h"
#include "Image/BackButton.h"
#include "Image/MatchingStart.h"

//�R���X�g���N�^
MatchingScene::MatchingScene(GameObject* parent)
	: GameObject(parent, "MatchingScene"),mouseMoob_(true),matching_(-1)
{
}

//������
void MatchingScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<BackButton>(this);
	Instantiate<MatchingStart>(this);
}

//�X�V
void MatchingScene::Update()
{
	if (Input::IsKeyDown(DIK_W))
	{
		matching_++;
		mouseMoob_ = false;
		if (matching_ >= MAX_MATCHING)
		{
			matching_ = MATCHING_BACK;
		}
	}
	if (Input::IsKeyDown(DIK_S))
	{
		matching_--;
		mouseMoob_ = false;
		if (matching_ < 0)
		{
			matching_ = MATCHING_STRAT;
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

	if (FindObject("MatchingStart") == nullptr)
	{
		SCENE_CHANGE(SCENE_ID_PLAY);
	}
	
	//�L�[����
	if (mouseMoob_ == false)
	{
		if (matching_ == MATCHING_BACK && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_LOBBY);
		}
		if (matching_ == MATCHING_STRAT && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_PLAY);
		}
	}
}

//�`��
void MatchingScene::Draw()
{
}

//�J��
void MatchingScene::Release()
{
}