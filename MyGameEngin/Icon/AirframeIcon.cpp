#include "AirframeIcon.h"
#include "../Engine/Image.h"

//�R���X�g���N�^
AirframeIcon::AirframeIcon(GameObject* parent, std::string name)
	: GameObject(parent, name),hPict_(-1)
{
}

AirframeIcon::AirframeIcon(GameObject* parent)
	: AirframeIcon(parent, "AirframeIcon")
{
}

//������
void AirframeIcon::Initialize()
{
	Load();
	InitialPos_ = XMFLOAT3(0.9f, 0.65f, 0);
	transform_.position_ = InitialPos_;
}

//�X�V
void AirframeIcon::Update()
{
	AirframePos();

	transform_.position_ = XMFLOAT3((InitialPos_.x + (AirframePos_.x / 2100)), InitialPos_.y - (AirframePos_.z / 1200), 0);
}

//�`��
void AirframeIcon::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void AirframeIcon::Release()
{
}