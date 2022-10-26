#include "Course.h"
#include "Engine/Model.h"
//�R���X�g���N�^
Course::Course(GameObject* parent)
	: GameObject(parent, "Course"), hModel_(-1)
{
}

Course::~Course()
{
}

//������
void Course::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Assets\\DemoCourse3.fbx");
	assert(hModel_ >= 0);
	transform_.scale_.x = Size_;
	transform_.scale_.y = 25;
	transform_.scale_.z = Size_;
	Model::SetAlpha(hModel_, 200);
	Model::IsZBuffer(hModel_, false);
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
	//Model::SetAlpha(hModel_, 0xcf);
}

//�J��
void Course::Release()
{
}