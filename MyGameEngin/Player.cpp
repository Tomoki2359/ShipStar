#include "Player.h"
//�R���X�g���N�^
Player::Player(GameObject* parent)
	: Airframe(parent, "Player")
{
}

Player::~Player()
{
}

void Player::SetStatus()
{
	//���Ƃ�for����CSV��������
	status_[MAX_SPEAD] = 150;
	status_[ACCELE] = 200;
	status_[TURBO] = 150;
	status_[ENDURANCE] = 100;

	failName_ = "Assets\\oden.fbx.";	//�t�@�C���̖��O
	sCamera_ = true;	//�J����ON
	transform_.scale_.x = 0.25;
	transform_.scale_.y = 0.25;
	transform_.scale_.z = 0.25;
}