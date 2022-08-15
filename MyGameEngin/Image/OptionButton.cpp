#include "OptionButton.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
OptionButton::OptionButton(GameObject* parent)
	: GameObject(parent, "OptionButton"), hPict_(-1)
{
}

//������
void OptionButton::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\Button.png");
	assert(hPict_ >= 0);
	transform_.scale_.x = 0.25;
	transform_.scale_.y = 0.125;
	transform_.position_.y = 0.125;
}

//�X�V
void OptionButton::Update()
{
	XMFLOAT3 MousePos_;
	MousePos_ = Input::GetMousePosition();

	//�X�^�[�g�̓����蔻��
	if (MousePos_.x >= 570 && MousePos_.x <= 1050 && MousePos_.y >= 280 && MousePos_.y <= 415)
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
void OptionButton::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void OptionButton::Release()
{
}