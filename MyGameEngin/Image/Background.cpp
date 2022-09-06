#include "Background.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
Background::Background(GameObject* parent)
	: GameObject(parent, "Background"), hPict_(-1)
{
}

//������
void Background::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\Background.jpg");
	assert(hPict_ >= 0);
}

//�X�V
void Background::Update()
{
}

//�`��
void Background::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void Background::Release()
{
}