#include "ResultScene.h"
#include "Image/MatchingBackground.h"
#include "Image/ResultImage.h"
#include "Engine/Image.h"
#include "Engine/Time.h"
#include "Option.h"

//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene")
{
}

//������
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
	//�摜�f�[�^�̃��[�h
	for (int i = 0; i < 10; i++)
	{
		std::string data = texS + std::to_string(i) + texF;
		hPict_[i] = Image::Load(data);
		assert(hPict_[i] > NULL);
	}
}

//�X�V
void ResultScene::Update()
{
}

//�`��
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
		Time::GetTime();
		break;
	default:
		break;
	}
}

//�J��
void ResultScene::Release()
{
}