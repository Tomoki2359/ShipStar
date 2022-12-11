#include "OriginalStatus.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
OriginalStatus::OriginalStatus(GameObject* parent)
	: GameObject(parent, "OriginalStatus"), hPict_(-1)
{
}

//������
void OriginalStatus::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\OriginalStatus.png");
	assert(hPict_ >= 0);
	transform_.position_.x = 1.5f;
}

//�X�V
void OriginalStatus::Update()
{
}

//�`��
void OriginalStatus::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void OriginalStatus::Release()
{
}