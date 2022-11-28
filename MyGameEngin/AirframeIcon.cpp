#include "AirframeIcon.h"
#include "Engine/Image.h"

//�R���X�g���N�^
AirframeIcon::AirframeIcon(GameObject* parent, std::string name)
	: GameObject(parent, name), hPict_(-1)
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
}

//�X�V
void AirframeIcon::Update()
{
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