#include "MatchingCourse.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
MatchingCourse::MatchingCourse(GameObject* parent)
	: GameObject(parent, "MatchingCourse"), hPict_(-1)
{
}

//������
void MatchingCourse::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\MatchingCourse.png");
	assert(hPict_ >= 0);
	transform_.position_.y = 0.5f;
}

//�X�V
void MatchingCourse::Update()
{
}

//�`��
void MatchingCourse::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void MatchingCourse::Release()
{
}