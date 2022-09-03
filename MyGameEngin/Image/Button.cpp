#include "Button.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
Button::Button(GameObject* parent)
	: GameObject(parent, "Button"), hPict_(-1), change_(false)
{
}
Button::Button(GameObject* parent, std::string name)
	: GameObject(parent, name), hPict_(-1), change_(false)
{
}

//������
void Button::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(SetFile());
	assert(hPict_ >= 0);
	InitialPoint();
}

//�X�V
void Button::Update()
{
	//�}�E�X�̈ʒu�̎擾
	MousePos_ = Input::GetMousePosition();

	//�摜�̈ʒu
	if (IsImage() || change_ )
	{
		transform_.scale_.x = 1.1f;
		transform_.scale_.y = 1.1f;
		if (Input::IsMouceDown(0) || Input::IsKeyDown(DIK_Z))
			KillMe();
	}
	else
	{
		transform_.scale_.x = 1.0f;
		transform_.scale_.y = 1.0f;
	}

	change_ = false;
}

//�`��
void Button::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void Button::Release()
{
}

//�I������Ă��邩�ǂ���
void Button::IsButton()
{
	change_ = true;
}
