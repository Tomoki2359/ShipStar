#include "CurrentStatus.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
CurrentStatus::CurrentStatus(GameObject* parent)
	: GameObject(parent, "CurrentStatus"), hPict_(-1)
{
}

//������
void CurrentStatus::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\CurrentStatus.png");
	assert(hPict_ >= 0);
	transform_.position_.x = -0.5f;
}

//�X�V
void CurrentStatus::Update()
{
}

//�`��
void CurrentStatus::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void CurrentStatus::Release()
{
}