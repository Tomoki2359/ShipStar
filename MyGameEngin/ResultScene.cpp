#include "ResultScene.h"
#include "Image/MatchingBackground.h"
#include "Image/ResultImage.h"
#include "Engine/Image.h"
#include "Engine/Time.h"
#include "Option.h"
#include "Storage.h"

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene"), hPict_(), hPictRecord_()
{
}

//初期化
void ResultScene::Initialize()
{
	Time::Lock();
	SetScreen(0, 0, 0);
	Instantiate<ResultImage>(this);
	transform_.position_ = XMFLOAT3(0, 0, 0);
	transform_.rotate_ = XMFLOAT3(0, 0, 0);
	transform_.scale_ = XMFLOAT3(1, 1, 1);

	std::string texS = "Assets\\Numbers\\Num";
	std::string texF = ".png";
	//画像データのロード
	for (int i = 0; i < 10; i++)
	{
		std::string data = texS + std::to_string(i) + texF;
		hPict_[i] = Image::Load(data);
		assert(hPict_[i] > NULL);
	}

	hPictRecord_[Pict_Lately] = Image::Load("Assets\\ClearTime.png");
	hPictRecord_[Pict_Recbreak] = Image::Load("Assets\\RecordBreaking.png");
}

//更新
void ResultScene::Update()
{
}

//描画
void ResultScene::Draw()
{
	Transform tr = transform_;
	switch (Option::GetMode())
	{
	case MODE_SOLO:
	case MODE_VSCOM:
	case MODE_VSGHOST:
		tr.position_.x = -0.3f;
		Time::Draw(tr, 2);
		break;
	default:
		break;
	}
	tr = transform_;
	tr.position_.y = 0.4f;
	const float size = 1.3f;
	tr.scale_ = { size , size , size };
	Image::SetTransform(hPictRecord_[Pict_Lately], tr);
	Image::Draw(hPictRecord_[Pict_Lately]);

	if (Storage::IsBreaked())	//記録更新された場合にのみ表示
	{
		tr.position_.y = -0.3f;
		Image::SetTransform(hPictRecord_[Pict_Recbreak], tr);
		Image::Draw(hPictRecord_[Pict_Recbreak]);
	}
}

//開放
void ResultScene::Release()
{
}