#include "PlayBackground.h"
#include "../Engine/Image.h"
#include "../Player.h"
#include "../Ghost.h"
#include "../Option.h"

//�R���X�g���N�^
PlayBackground::PlayBackground(GameObject* parent)
	: GameObject(parent, "PlayBackground")
{
	hPict_[0] = -1;
	hPict_[1] = -1;
}

//������
void PlayBackground::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_[0] = Image::Load(L"Assets\\PlayBackground1.jpg");
	assert(hPict_[0] >= 0);

	hPict_[1] = Image::Load(L"Assets\\PlayBackground2.jpg");
	assert(hPict_[1] >= 0);
}

//�X�V
void PlayBackground::Update()
{
	if (Option::GetMode() != MODE_REPLAY &&
		Option::GetMode() != MODE_ONLYGHOST)
	{
		Player* pPlayer = (Player*)FindObject("Player");
		transform_.position_.x = -pPlayer->GetRotate().y / 800;
		SAFE_RELEASE(pPlayer);
	}
	else
	{
		Ghost* pGhost = (Ghost*)FindObject("Ghost");
		transform_.position_.x = -pGhost->GetRotate().y / 800;
		SAFE_RELEASE(pGhost);
	}
}

//�`��
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

//�J��
void PlayBackground::Release()
{
}