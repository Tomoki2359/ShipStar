#include "PlayBackground.h"
#include "../Engine/Image.h"
#include "../Player.h"

//コンストラクタ
PlayBackground::PlayBackground(GameObject* parent)
	: GameObject(parent, "PlayBackground")
{
	hPict_[0] = -1;
	hPict_[1] = -1;
}

//初期化
void PlayBackground::Initialize()
{
	//モデルデータのロード
	hPict_[0] = Image::Load(L"Assets\\PlayBackground1.jpg");
	assert(hPict_[0] >= 0);

	hPict_[1] = Image::Load(L"Assets\\PlayBackground2.jpg");
	assert(hPict_[1] >= 0);
}

//更新
void PlayBackground::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
	transform_.position_.x = -pPlayer->GetRotate().y / 800;
}

//描画
void PlayBackground::Draw()
{
	Transform trans = transform_;
	trans.position_.x -= 1;
	Image::SetTransform(hPict_[0], trans);
	Image::Draw(hPict_[0]);

	trans.position_.x += 2;
	Image::SetTransform(hPict_[1], trans);
	Image::Draw(hPict_[1]);
}

//開放
void PlayBackground::Release()
{
}