#include "CourseOutObject.h"
#include "Engine/Model.h"

CourseOutObject::CourseOutObject(GameObject* parent)
	: GameObject(parent, "CourseOutObject"), hModel_(-1)
{
}

CourseOutObject::~CourseOutObject()
{
}

void CourseOutObject::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Assets\\temporary\\Parrot.fbx");
	assert(hModel_ >= 0);
}

void CourseOutObject::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}
