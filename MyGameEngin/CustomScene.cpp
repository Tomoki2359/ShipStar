#include "CustomScene.h"
#include "Image/OKButton.h"
#include "Image/BackButton.h"

//�R���X�g���N�^
CustomScene::CustomScene(GameObject* parent)
	: GameObject(parent, "CustomScene"),mouseMoob_(true),custom_(-1),change_(false)
{
}

//������
void CustomScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<OKButton>(this);
	Instantiate<BackButton>(this);
}

//�X�V
void CustomScene::Update()
{
	if (Input::IsKeyDown(DIK_W))
	{
		custom_++;
		mouseMoob_ = false;
		if (custom_ >= MAX_CUSTOM)
		{
			custom_ = CUSTOM_BACK;
		}
	}
	if (Input::IsKeyDown(DIK_S))
	{
		custom_--;
		mouseMoob_ = false;
		if (custom_ < 0)
		{
			custom_ = CUSTOM_OK;
		}
	}

	//�}�E�X�����������ǂ���
	mousePos_ = mouseNext_;
	mouseNext_ = Input::GetMousePosition();
	if (mousePos_.x != mouseNext_.x && mousePos_.y != mouseNext_.y)
	{
		mouseMoob_ = true;
	}

	//�ύX���邩�ǂ���
	if (change_ == false)
	{
		if (FindObject("BackButton") == nullptr)
		{
			SCENE_CHANGE(SCENE_ID_LOBBY);
		}

		if (FindObject("OKButton") == nullptr)
		{
			Instantiate<OKButton>(this);
			change_ = true;
		}

		//�L�[����
		if (mouseMoob_ == false)
		{
			if (custom_ == CUSTOM_BACK && Input::IsKeyDown(DIK_Z))
			{
				SCENE_CHANGE(SCENE_ID_LOBBY);
			}
			if (custom_ == CUSTOM_OK && Input::IsKeyDown(DIK_Z))
			{
				change_ = true;
			}
		}
	}

	//�{���ɕύX���邩�ǂ���
	if (change_ == true)
	{
		if (FindObject("BackButton") == nullptr)
		{
			Instantiate<BackButton>(this);
			change_ = false;
		}

		if (FindObject("OKButton") == nullptr)
		{
			Instantiate<OKButton>(this);
			change_ = false;
		}

		//�L�[����
		if (mouseMoob_ == false)
		{
			if (custom_ == CUSTOM_BACK && Input::IsKeyDown(DIK_Z))
			{
				change_ = false;
			}
			if (custom_ == CUSTOM_OK && Input::IsKeyDown(DIK_Z))
			{
				change_ = false;
			}
		}
	}
}

//�`��
void CustomScene::Draw()
{
}

//�J��
void CustomScene::Release()
{
}