#include "ButtonArrangement.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
ButtonArrangement::ButtonArrangement(GameObject* parent)
	: GameObject(parent, "ButtonArrangement"), hPict_(-1)
{
}

//������
void ButtonArrangement::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\ButtonArrangement.png");
	assert(hPict_ >= 0);
}

//�X�V
void ButtonArrangement::Update()
{
}

//�`��
void ButtonArrangement::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void ButtonArrangement::Release()
{
}