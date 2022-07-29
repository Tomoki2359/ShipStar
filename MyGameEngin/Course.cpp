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
	hModel_ = Model::Load("Assets\\Ground.fbx");
	assert(hModel_ >= 0);
	transform_.scale_.x = 5;
	transform_.scale_.y = 3;
	transform_.scale_.z = 5;
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