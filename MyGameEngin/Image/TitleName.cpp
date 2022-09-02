#include "TitleName.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
TitleName::TitleName(GameObject* parent)
	: GameObject(parent, "TitleName"), hPict_(-1)
{
}

//������
void TitleName::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\Title.png");
	assert(hPict_ >= 0);
	transform_.position_.y = 0.5f;
}

//�X�V
void TitleName::Update()
{
}

//�`��
void TitleName::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void TitleName::Release()
{
}