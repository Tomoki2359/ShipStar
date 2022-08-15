#include "TitleStart.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
TitleStart::TitleStart(GameObject* parent)
	: GameObject(parent, "TitleStart"), hPict_(-1)
{
}

//������
void TitleStart::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\Button.png");
	assert(hPict_ >= 0);
	transform_.scale_.x = 0.25;
	transform_.scale_.y = 0.125;
	transform_.position_.y = -0.25;
}

//�X�V
void TitleStart::Update()
{
	XMFLOAT3 MousePos_;
	MousePos_ = Input::GetMousePosition();

	//�X�^�[�g�̓����蔻��
	if (MousePos_.x >= 570 && MousePos_.x <= 1050 && MousePos_.y >= 465 && MousePos_.y <= 600)
	{
		transform_.scale_.x = 0.3;
		transform_.scale_.y = 0.2;
		if (Input::IsMouceDown(0))
			KillMe();
	}
	else
	{
		transform_.scale_.x = 0.25;
		transform_.scale_.y = 0.125;
	}
}

//�`��
void TitleStart::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void TitleStart::Release()
{
}