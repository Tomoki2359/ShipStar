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
	hModel_ = Model::Load("Assets\\temporary\\Parrot.fbx");
	assert(hModel_ >= 0);
}

void GoalObject::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}
