#include "CouseMap.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
CouseMap::CouseMap(GameObject* parent)
	: GameObject(parent, "CouseMap"), hPict_(-1)
{
}

//������
void CouseMap::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\CouseMap1.png");
	assert(hPict_ >= 0);
	transform_.scale_.x = 0.125f;
	transform_.scale_.y = 0.125f;
	transform_.position_.x = 0.8;
	transform_.position_.y = 0.7;
}

//�X�V
void CouseMap::Update()
{
}

//�`��
void CouseMap::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void CouseMap::Release()
{
}