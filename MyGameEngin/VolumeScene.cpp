#include "VolumeScene.h"
#include "Image/BackButton.h"
#include "Image/OKButton.h"

//�R���X�g���N�^
VolumeScene::VolumeScene(GameObject* parent)
	: GameObject(parent, "VolumeScene"),mouseMoob_(false),volume_(-1)
{
}

//������
void VolumeScene::Initialize()
{
	Instantiate<BackButton>(this);
	Instantiate<OKButton>(this);
	SetScreen(0, 0, 0);
}

//�X�V
void VolumeScene::Update()
{
	if (Input::IsKeyDown(DIK_W))
	{
		mouseMoob_ = false;
		volume_++;
		if (volume_ >= MAX_VOLUME)
		{
			volume_ = VOLUME_BACK;
		}
	}
	if (Input::IsKeyDown(DIK_S))
	{
		mouseMoob_ = false;
		volume_--;
		if (volume_ < 0)
		{
			volume_ = VOLUME_OK;
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
		SCENE_CHANGE(SCENE_ID_OPTION);
	}
	if (FindObject("OKButton") == nullptr)
	{
		SCENE_CHANGE(SCENE_ID_OPTION);
	}

	//�L�[����
	if (mouseMoob_ == false)
	{
		if (volume_ == VOLUME_BACK && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_OPTION);
		}
		if (volume_ == VOLUME_OK && Input::IsKeyDown(DIK_Z))
		{
			SCENE_CHANGE(SCENE_ID_OPTION);
		}
	}
}

//�`��
void VolumeScene::Draw()
{
}

//�J��
void VolumeScene::Release()
{
}