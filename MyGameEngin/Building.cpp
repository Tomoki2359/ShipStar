#include "Building.h"
#include "Engine/Model.h"
//コンストラクタ
Building::Building(GameObject* parent)
	: GameObject(parent, "Building"), hModel_(-1)
{
}

Building::~Building()
{
}

//初期化
void Building::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Assets\\Building.fbx");
	assert(hModel_ >= 0);
	transform_.scale_.x = Size_;
	transform_.scale_.y = 10;
	transform_.scale_.z = Size_;
	//Model::IsZBuffer(hModel_, false);
}

//更新
void Building::Update()
{
}

//描画
void Building::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	//Model::SetAlpha(hModel_, 0xcf);
}

//開放
void Building::Release()
{
}