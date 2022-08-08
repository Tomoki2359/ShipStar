#include "Player.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
	: Airframe(parent, "Player")
{
}

Player::~Player()
{
}

void Player::UpdateState()
{
	//�O�i����
	if (Input::IsKey(DIK_W) && !Input::IsKey(DIK_S))
	{
		Accelerate();
	}
	//�u���[�L����
	if (Input::IsKey(DIK_S) && !Input::IsKey(DIK_W))
	{
		Decelerate();
	}
	//���ɃJ�[�u����
	if (Input::IsKey(DIK_A) && !Input::IsKey(DIK_D))
	{
		TurnLeft();
	}
	//�E�ɃJ�[�u����
	if (Input::IsKey(DIK_D) && !Input::IsKey(DIK_A))
	{
		TurnRight();
	}
	//�㏸����
	if (Input::IsKey(DIK_E) && !Input::IsKey(DIK_Q))
	{
		Rise();
	}
	//���~����
	if (Input::IsKey(DIK_Q) && !Input::IsKey(DIK_E))
	{
		Descent();
	}
	//�^�[�{
	//300�͏��ʂɂ���Ĕ������鎞�Ԃ��ϓ�����(�ŉ��ʂ���5�b,10�b,15�b,20�b)
	if (tTurbo_ >= 300 && Input::IsKeyDown(DIK_C))
	{
		tTurbo_ = 0;
		Turbo();
	}
}

//void Player::SetStatus()
//{
//	//���Ƃ�for����CSV��������
//	status_[MAX_SPEED] = 150;
//	status_[ACCELE] = 200;
//	status_[TURBO] = 150;
//	status_[ENDURANCE] = 100;
//
//	//�p�[�c���Ăяo����悤�ɂȂ�����C��
//	fileName_ = "Assets\\oden.fbx.";	//�t�@�C���̖��O
//	cCamera_ = true;	//�J����ON
//	transform_.scale_.x = 0.25;
//	transform_.scale_.y = 0.25;
//	transform_.scale_.z = 0.25;
//}