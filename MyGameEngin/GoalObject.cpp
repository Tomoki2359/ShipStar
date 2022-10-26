#include "GoalObject.h"
#include "Engine/Model.h"

GoalObject::GoalObject(GameObject* parent)
	: GameObject(parent, "GoalObject"), hModel_(-1)
{
}

GoalObject::~GoalObject()
{
}

void GoalObject::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Assets\\goal.fbx");
	assert(hModel_ >= 0);
	transform_.scale_.y = 0.75;
	transform_.scale_.x = 0.75;
}

void GoalObject::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}
