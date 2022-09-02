#include "TitleOption.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
TitleOption::TitleOption(GameObject* parent)
	: GameObject(parent, "TitleOption"), hPict_(-1)
{
}

//������
void TitleOption::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\TitleOption.png");
	assert(hPict_ >= 0);
	transform_.position_.y = -0.5f;
}

//�X�V
void TitleOption::Update()
{
	//�}�E�X�̈ʒu�̎擾
	XMFLOAT3 MousePos_;
	MousePos_ = Input::GetMousePosition();

	//�摜�̈ʒu
	if (MousePos_.x >= 570 && MousePos_.x <= 1050 && MousePos_.y > 600 && MousePos_.y <= 735)
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
void TitleOption::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void TitleOption::Release()
{
}