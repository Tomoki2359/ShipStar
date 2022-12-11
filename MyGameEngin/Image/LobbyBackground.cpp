#include "LobbyBackground.h"
#include "../Engine/Image.h"
#include "../Player.h"

//�R���X�g���N�^
LobbyBackground::LobbyBackground(GameObject* parent)
	: GameObject(parent, "LobbyBackground"), hPict_(-1)
{
}

//������
void LobbyBackground::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\LobbyBackground.png");
	assert(hPict_ >= 0);
	Image::IsDifference(hPict_,false);
}

//�X�V
void LobbyBackground::Update()
{
}

//�`��
void LobbyBackground::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void LobbyBackground::Release()
{
}