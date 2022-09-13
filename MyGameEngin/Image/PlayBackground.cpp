#include "PlayBackground.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
PlayBackground::PlayBackground(GameObject* parent)
	: GameObject(parent, "PlayBackground")
{
	hPict_[0] = -1;
	hPict_[1] = -1;
}

//������
void PlayBackground::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_[0] = Image::Load(L"Assets\\PlayBackground1.jpg");
	assert(hPict_[0] >= 0);

	hPict_[1] = Image::Load(L"Assets\\PlayBackground1.jpg");
	assert(hPict_[1] >= 0);
}

//�X�V
void PlayBackground::Update()
{
}

//�`��
void PlayBackground::Draw()
{
	Transform trans = transform_;
	Image::SetTransform(hPict_[0], trans);
	Image::Draw(hPict_[0]);

	trans.position_.x += 2;
	Image::SetTransform(hPict_[1], trans);
	Image::Draw(hPict_[1]);
}

//�J��
void PlayBackground::Release()
{
}