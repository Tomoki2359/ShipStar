#include "Building.h"
#include "Engine/Model.h"
//�R���X�g���N�^
Building::Building(GameObject* parent)
	: GameObject(parent, "Building"), hModel_(-1)
{
}

Building::~Building()
{
}

//������
void Building::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Assets\\Building.fbx");
	assert(hModel_ >= 0);
	transform_.scale_.x = Size_;
	transform_.scale_.y = 10;
	transform_.scale_.z = Size_;
	//Model::IsZBuffer(hModel_, false);
}

//�X�V
void Building::Update()
{
}

//�`��
void Building::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	//Model::SetAlpha(hModel_, 0xcf);
}

//�J��
void Building::Release()
{
}