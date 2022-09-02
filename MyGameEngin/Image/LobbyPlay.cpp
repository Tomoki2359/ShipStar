#include "LobbyPlay.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
LobbyPlay::LobbyPlay(GameObject * parent)
	: GameObject(parent, "LobbyPlay"), hPict_(-1)
{
}

//������
void LobbyPlay::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\LobbyPlay.png");
	assert(hPict_ >= 0);
	transform_.position_.x = 0.7f;
	transform_.position_.y = 0.7f;
}

//�X�V
void LobbyPlay::Update()
{
	//�}�E�X�̈ʒu�̎擾
	XMFLOAT3 MousePos_;
	MousePos_ = Input::GetMousePosition();

	//�摜�̈ʒu
	if (MousePos_.x >= 1250 && MousePos_.x <= 1520 && MousePos_.y >= 5 && MousePos_.y <= 150)
	{
		transform_.scale_.x = 1.1;
		transform_.scale_.y = 1.1;
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
void LobbyPlay::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void LobbyPlay::Release()
{
}