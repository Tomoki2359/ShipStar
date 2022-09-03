#include "LobbyScene.h"

//�R���X�g���N�^
LobbyScene::LobbyScene(GameObject* parent)
	: GameObject(parent, "LobbyScene"),mouseMoob_(true),lobby_(-1), first_(true)
{
}

//������
void LobbyScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<LobbyCourse>(this);
	Instantiate<LobbyCustom>(this);
	Instantiate<LobbyPlay>(this);
}

//�X�V
void LobbyScene::Update()
{
	if (first_)
	{
		first_ = false;
		pCourse_ = (LobbyCourse*)FindObject("LobbyCourse");
		assert(pCourse_ != nullptr);
		pPlay_ = (LobbyPlay*)FindObject("LobbyPlay");
		assert(pPlay_ != nullptr);
		pCustom_ = (LobbyCustom*)FindObject("LobbyCustom");
		assert(pCustom_ != nullptr);
	}
	if (Input::IsKeyDown(DIK_S))
	{
		mouseMoob_ = false;
		lobby_++;
		if (lobby_ >= MAX_LOBBY)
		{
			lobby_ = LOBBY_COURSE;
		}
	}
	if (Input::IsKeyDown(DIK_W))
	{
		mouseMoob_ = false;
		lobby_--;
		if (lobby_ < 0)
		{
			lobby_ = LOBBY_CUSTOM;
		}
	}

	//�}�E�X�����������ǂ���
	mousePos_ = mouseNext_;
	mouseNext_ = Input::GetMousePosition();
	if (mousePos_.x != mouseNext_.x && mousePos_.y != mouseNext_.y)
	{
		mouseMoob_ = true;
	}

	if (FindObject("LobbyPlay") == nullptr)
	{
			SCENE_CHANGE(SCENE_ID_MATCHING);
	}
	

	if (FindObject("LobbyCustom") == nullptr)
	{
			SCENE_CHANGE(SCENE_ID_CUSTOM);
	}

	//�L�[����
	if (mouseMoob_ == false)
	{
		if (lobby_ == LOBBY_COURSE)
		{
			pCourse_->IsButton();
		}
		if (lobby_ == LOBBY_PLAY)
		{
			pPlay_->IsButton();
		}
		if (lobby_ == LOBBY_CUSTOM)
		{
			pCustom_->IsButton();
		}
	}
}

//�`��
void LobbyScene::Draw()
{
}

//�J��
void LobbyScene::Release()
{
}