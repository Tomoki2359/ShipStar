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
	//モデルデータのロード
	hModel_ = Model::Load("Assets\\temporary\\Parrot.fbx");
	assert(hModel_ >= 0);

	const float Size = 0.1f;
	//transform_.scale_ = XMFLOAT3(Size, Size, Size);
}

void CourseOutObject::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}
