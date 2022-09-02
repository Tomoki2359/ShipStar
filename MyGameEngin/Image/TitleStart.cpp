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
	hPict_ = Image::Load(L"Assets\\TitleStart.png");
	assert(hPict_ >= 0);
	transform_.position_.y = -0.25f;
}

//�X�V
void TitleStart::Update()
{
	//�}�E�X�̈ʒu�̎擾
	XMFLOAT3 MousePos_;
	MousePos_ = Input::GetMousePosition();

	//�摜�̈ʒu
	if (MousePos_.x >= 570 && MousePos_.x <= 1050 && MousePos_.y >= 465 && MousePos_.y <= 600)
	{
		transform_.scale_.x = 1.1f;
		transform_.scale_.y = 1.1f;
		if (Input::IsMouceDown(0))
			KillMe();
	}
	else
	{
		transform_.scale_.x = 1.0f;
		transform_.scale_.y = 1.0f;
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