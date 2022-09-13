#include "PlayBackground.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
PlayBackground::PlayBackground(GameObject* parent)
	: GameObject(parent, "PlayBackground")
{
	hPict[0] =
}

//������
void PlayBackground::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\PlayBackground.jpg");
	assert(hPict_ >= 0);
}

//�X�V
void PlayBackground::Update()
{
}

//�`��
void PlayBackground::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void PlayBackground::Release()
{
}