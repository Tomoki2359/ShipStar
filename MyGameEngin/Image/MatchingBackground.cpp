#include "MatchingBackground.h"
#include "../Engine/Image.h"
#include "../Player.h"

//�R���X�g���N�^
MatchingBackground::MatchingBackground(GameObject* parent)
	: GameObject(parent, "MatchingBackground"), hPict_(-1)
{
}

//������
void MatchingBackground::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\MatchingBackground.png");
	assert(hPict_ >= 0);
}

//�X�V
void MatchingBackground::Update()
{
}

//�`��
void MatchingBackground::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void MatchingBackground::Release()
{
}