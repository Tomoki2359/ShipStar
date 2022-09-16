#include "Course.h"
#include "Engine/Model.h"
//コンストラクタ
Course::Course(GameObject* parent)
	: GameObject(parent, "Course"), hModel_(-1)
{
}

Course::~Course()
{
}

//初期化
void Course::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Assets\\DemoCourse2.fbx");
	assert(hModel_ >= 0);
	transform_.scale_.x = Size_;
	transform_.scale_.y = 10;
	transform_.scale_.z = Size_;
}

//更新
void Course::Update()
{
}

//描画
void Course::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Course::Release()
{
}