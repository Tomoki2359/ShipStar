#include "PartsList.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
PartsList::PartsList(GameObject* parent)
	: GameObject(parent, "PartsList"), hPict_(-1)
{
}

//������
void PartsList::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\PartsList.png");
	assert(hPict_ >= 0);
	transform_.position_.x = 0.5f;
}

//�X�V
void PartsList::Update()
{
}

//�`��
void PartsList::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void PartsList::Release()
{
}