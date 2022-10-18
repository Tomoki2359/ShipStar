#include "ButtonScene.h"
#include "Image/ButtonArrangement.h"

//�R���X�g���N�^
ButtonScene::ButtonScene(GameObject* parent)
	: GameObject(parent, "ButtonScene"), mouseMoob_(false), button_(-1),first_(true)
{
}

//������
void ButtonScene::Initialize()
{
	Instantiate<BackButton>(this);
	Instantiate<OKButton>(this);
	Instantiate<ButtonArrangement>(this);
	SetScreen(0, 0, 0);
}

//�X�V
void ButtonScene::Update()
{
	if (first_)
	{
		first_ = false;
		pBack_ = (BackButton*)FindObject("BackButton");
		assert(pBack_ != nullptr);
		pOK_ = (OKButton*)FindObject("OKButton");
		assert(pOK_ != nullptr);
	}
	if (Input::IsKeyDown(DIK_S))
	{
		mouseMoob_ = false;
		button_++;
		if (button_ >= MAX_BUTTON)
		{
			button_ = BUTTON_BACK;
		}
	}
	if (Input::IsKeyDown(DIK_W))
	{
		mouseMoob_ = false;
		button_--;
		if (button_ < 0)
		{
			button_ = BUTTON_OK;
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
		if (button_ == BUTTON_BACK)
		{
			pBack_->IsButton();
		}
		if (button_ == BUTTON_OK)
		{
			pOK_->IsButton();
		}
	}
}

//�`��
void ButtonScene::Draw()
{
}

//�J��
void ButtonScene::Release()
{
}