#include "LobbyCustom.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
LobbyCustom::LobbyCustom(GameObject* parent)
	: GameObject(parent, "LobbyCustom"), hPict_(-1)
{
}

//������
void LobbyCustom::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\Button.png");
	assert(hPict_ >= 0);
	transform_.scale_.x = 0.166f;
	transform_.scale_.y = 0.166f;
	transform_.position_.x = 0.8f;
	transform_.position_.y = -0.8f;
}

//�X�V
void LobbyCustom::Update()
{
	XMFLOAT3 MousePos_;
	MousePos_ = Input::GetMousePosition();
	//if (MousePos_.x >= 1580 && MousePos_.x <= 1920 && MousePos_.y >= 880 && MousePos_.y <= 1080)
	if (MousePos_.x >= 1250 && MousePos_.x <= 1520 && MousePos_.y >= 650 && MousePos_.y <= 1080)
	{
		transform_.scale_.x = 0.25f;
		transform_.scale_.y = 0.25f;
		if (Input::IsMouceDown(0))
			KillMe();
	}
	else
	{
		transform_.scale_.x = 0.166f;
		transform_.scale_.y = 0.166f;
	}
}

//�`��
void LobbyCustom::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void LobbyCustom::Release()
{
}