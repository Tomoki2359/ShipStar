#include "ChangeStatus.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
ChangeStatus::ChangeStatus(GameObject* parent)
	: GameObject(parent, "ChangeStatus"), hPict_(-1)
{
}

//������
void ChangeStatus::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\ChangeStatus.png");
	assert(hPict_ >= 0);
	transform_.position_.x = 0.5f;
}

//�X�V
void ChangeStatus::Update()
{
}

//�`��
void ChangeStatus::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void ChangeStatus::Release()
{
}