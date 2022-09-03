#include "Course.h"
#include "Engine/Model.h"
//�R���X�g���N�^
Course::Course(GameObject* parent)
	: GameObject(parent, "Course"), hModel_(-1)
{
}

//������
void Course::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Assets\\Course2.fbx");
	assert(hModel_ >= 0);
	transform_.scale_.x = 55;
	transform_.scale_.y = 7;
	transform_.scale_.z = 55;
	transform_.rotate_.y = 90;
}

//�X�V
void Course::Update()
{
}

//�`��
void Course::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Course::Release()
{
}